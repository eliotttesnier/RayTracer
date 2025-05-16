//
// Created by roussierenoa on 5/2/25.
//

#include "Core.hpp"

#include <dirent.h>
#include <sys/types.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Factory/Factory.hpp"
#include "Parser/Parser.hpp"
#include "Renderer.hpp"
#include "../GraphicRenderer/GraphicRenderer.hpp"

void RayTracer::Core::_loadPlugins()
{
    try {
        std::string pluginDir = "./plugins";
        DIR *dir = opendir(pluginDir.c_str());
        if (!dir) {
            std::cerr << "Plugin directory doesn't exist or is not a directory: ./plugins"
                      << std::endl;
            return;
        }
        #ifdef _DEBUG
                std::cout << std::endl << "Loading plugins..." << std::endl;
        #endif

        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string path = pluginDir + "/" + entry->d_name;
            std::string name = entry->d_name;
            if (name.length() > 3 && name.substr(name.length() - 3) == ".so") {
                name = name.substr(3, name.length() - 6);
                this->_plugins[name] = std::make_shared<Loader::LibLoader>();
                this->_plugins[name]->openLib(path);
            }
        }
        closedir(dir);
    } catch (const std::exception &e) {
        std::cerr << "Error loading plugins: " << e.what() << std::endl;
    }
}

void RayTracer::Core::_handleCameraMovement(
    const std::string &configFileName,
    runResult_e result
)
{
    Math::Point3D movementOffset(0.0, 0.0, 0.0);
    const float MOVEMENT_AMOUNT = 2.0f;

    if (result == MOVE_FORWARD)
        movementOffset = Math::Point3D(0.0, 0.0, -MOVEMENT_AMOUNT);
    if (result == MOVE_BACKWARD)
        movementOffset = Math::Point3D(0.0, 0.0, MOVEMENT_AMOUNT);
    if (result == MOVE_RIGHT)
        movementOffset = Math::Point3D(MOVEMENT_AMOUNT, 0.0, 0.0);
    if (result == MOVE_LEFT)
        movementOffset = Math::Point3D(-MOVEMENT_AMOUNT, 0.0, 0.0);
    if (result == MOVE_UP)
        movementOffset = Math::Point3D(0.0, MOVEMENT_AMOUNT, 0.0);
    if (result == MOVE_DOWN)
        movementOffset = Math::Point3D(0.0, -MOVEMENT_AMOUNT, 0.0);

    _runProg(configFileName, Math::Point3D(
        _cameraOffset._x + movementOffset._x,
        _cameraOffset._y + movementOffset._y,
        _cameraOffset._z + movementOffset._z
    ));
}

void RayTracer::Core::_runProg(
    const std::string &configFileName,
    const Math::Point3D &additionalOffset
)
{
    _parser = std::make_unique<RayTracer::Parser::Parser>(configFileName.c_str());
    _cameraOffset = Math::Point3D(
        additionalOffset._x,
        additionalOffset._y,
        additionalOffset._z
    );

    this->_loadPlugins();
    this->_sceneElements = RayTracer::Factory::Factory::createElement(
        this->_parser->getCameraConfig(),
        this->_parser->getPrimitivesConfig(),
        this->_parser->getLightConfig(),
        this->_plugins
    );

    auto camera = std::get<2>(this->_sceneElements);
    Math::Point3D currentPos = camera->getPosition();
    camera->setPosition(
        currentPos._x + _cameraOffset._x,
        currentPos._y + _cameraOffset._y,
        currentPos._z + _cameraOffset._z
    );

    auto renderingConfig = _parser->getRenderingConfig();
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(
        this->getCamera(),
        this->getPrimitives(),
        this->getLights()
    );
    renderer->setMultithreading(renderingConfig.getMultithreading());
    renderer->setMaxThreads(renderingConfig.getMaxThreads());
    if (renderingConfig.getType() == "preview")
        renderer->renderPreview();

    if (!_graphicRendererInitialized) {
        _graphicRenderer = std::make_unique<GraphicRenderer>(
            configFileName.c_str(),
            "preview.ppm",
            "output.ppm",
            renderingConfig.getType() == "preview",
            renderingConfig.getType() == "progressive"
        );
        _graphicRendererInitialized = true;
    }
    _graphicRenderer->setProgressiveMode(
        renderingConfig.getType() == "progressive"
    );
    _graphicRenderer->setPreviewMode(
        renderingConfig.getType() == "preview"
    );

    bool isProgressiveMode = (renderingConfig.getType() == "progressive");

    if (isProgressiveMode) {
        renderer->registerUpdateCallback(
            [this](const std::vector<std::vector<Graphic::color_t>> &pixelBuffer) {
                this->_graphicRenderer->updateProgressiveRendering(pixelBuffer);
            }
        );
    }

    this->applyRenderingConfig(renderer);
    this->applyAntialiasing(renderer);

    std::atomic<bool> renderingComplete(false);

    std::thread renderThread([&]() {
        renderer->render();
        renderingComplete = true;
    });

    runResult_e result = _graphicRenderer->run(renderingComplete);

    if (result == RELOAD_CONFIG) {
        renderer->stopThreads();
        if (renderThread.joinable())
            renderThread.join();
        _runProg(configFileName, _cameraOffset);
        return;
    }

    if (result != NOTHING && result != FINISHED && result != RELOAD_CONFIG) {
        renderer->stopThreads();
        if (renderThread.joinable())
            renderThread.join();
        _handleCameraMovement(configFileName, result);
        return;
    }

    if (renderThread.joinable())
        renderThread.join();

    if (!isProgressiveMode)
        _graphicRenderer->switchToFinalImage();
    _graphicRenderer->exportToPNG("output.png");
}

RayTracer::Core::Core(
    char **av
) : _parser(std::make_unique<RayTracer::Parser::Parser>(av[1])), _cameraOffset(0.0, 0.0, 0.0)
{
    this->_runProg(av[1], _cameraOffset);
}

std::vector<std::shared_ptr<IPrimitive>> RayTracer::Core::getPrimitives() const
{
    return std::get<0>(this->_sceneElements);
}

std::vector<std::shared_ptr<ILight>> RayTracer::Core::getLights() const
{
    return std::get<1>(this->_sceneElements);
}

std::shared_ptr<RayTracer::Camera> RayTracer::Core::getCamera() const
{
    return std::get<2>(this->_sceneElements);
}

void RayTracer::Core::applyAntialiasing(const std::unique_ptr<Renderer> &renderer) const
{
    auto antialiasingConfig = _parser->getAntialiasingConfig();

    if (antialiasingConfig.getType() == "supersampling") {
        renderer->setAntialiasingMode(Renderer::SUPERSAMPLING);
        renderer->setSupersamplingLevel(antialiasingConfig.getSamples());
    } else if (antialiasingConfig.getType() == "adaptive") {
        renderer->setAntialiasingMode(Renderer::ADAPTIVE_SUPERSAMPLING);
        renderer->setAdaptiveThreshold(antialiasingConfig.getThreshold());
    } else {
        renderer->setAntialiasingMode(Renderer::NONE);
    }
}

void RayTracer::Core::applyRenderingConfig(const std::unique_ptr<Renderer> &renderer) const
{
    auto renderingConfig = _parser->getRenderingConfig();

    if (renderingConfig.getType() == "progressive") {
        renderer->setRenderingMode(Renderer::PROGRESSIVE);
    } else {
        renderer->setRenderingMode(Renderer::PREVIEW);
    }
}
