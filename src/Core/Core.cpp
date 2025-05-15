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
                this->_plugins[name] = std::make_unique<Loader::LibLoader>();
                this->_plugins[name]->openLib(path);
            }
        }
        closedir(dir);
    } catch (const std::exception& e) {
        std::cerr << "Error loading plugins: " << e.what() << std::endl;
    }
}

void RayTracer::Core::_handleCameraMovement(char **av)
{
    const char* cameraMoveEnv = getenv("RAYTRACER_CAMERA_MOVE");
    if (cameraMoveEnv == nullptr) {
        Core reCore(av, Math::Point3D(0.0, 0.0, 0.0));
        return;
    }

    std::string cameraMove(cameraMoveEnv);
    unsetenv("RAYTRACER_CAMERA_MOVE");
    Math::Point3D movementOffset(0.0, 0.0, 0.0);
    const float MOVEMENT_AMOUNT = 2.0f;

    if (cameraMove == "forward")
        movementOffset = Math::Point3D(0.0, 0.0, -MOVEMENT_AMOUNT);
    if (cameraMove == "backward")
        movementOffset = Math::Point3D(0.0, 0.0, MOVEMENT_AMOUNT);
    if (cameraMove == "right")
        movementOffset = Math::Point3D(MOVEMENT_AMOUNT, 0.0, 0.0);
    if (cameraMove == "left")
        movementOffset = Math::Point3D(-MOVEMENT_AMOUNT, 0.0, 0.0);
    if (cameraMove == "up")
        movementOffset = Math::Point3D(0.0, MOVEMENT_AMOUNT, 0.0);
    if (cameraMove == "down")
        movementOffset = Math::Point3D(0.0, -MOVEMENT_AMOUNT, 0.0);

    Core reCore(av, movementOffset);
}

RayTracer::Core::Core(char **av
):
    _parser(av[1]), _cameraOffset(0.0, 0.0, 0.0)
{
    this->_loadPlugins();
    this->_sceneElements = RayTracer::Factory::Factory::createElement(
        this->_parser.getCameraConfig(),
        this->_parser.getPrimitivesConfig(),
        this->_parser.getLightConfig(),
        this->_plugins
    );

    auto renderingConfig = _parser.getRenderingConfig();
    Renderer renderer(this->getCamera(), this->getPrimitives(), this->getLights());
    renderer.setMultithreading(renderingConfig.getMultithreading());
    renderer.setMaxThreads(renderingConfig.getMaxThreads());
    if (renderingConfig.getType() == "preview")
        renderer.renderPreview();

    GraphicRenderer graphicRenderer(
        av[1],
        "preview.ppm",
        "output.ppm",
        renderingConfig.getType() == "preview",
        renderingConfig.getType() == "progressive"
    );
    bool isProgressiveMode = (renderingConfig.getType() == "progressive");

    if (isProgressiveMode) {
        renderer.registerUpdateCallback([&graphicRenderer](
                const std::vector<std::vector<Graphic::color_t>>& pixelBuffer) {
            graphicRenderer.updateProgressiveRendering(pixelBuffer);
        });
    }

    this->applyRenderingConfig(renderer);
    this->applyAntialiasing(renderer);

    std::atomic<bool> renderingComplete(false);

    std::thread renderThread([&]() {
        renderer.render();
        renderingComplete = true;
    });

    runResult_e result = graphicRenderer.run(renderingComplete);

    if (result == RELOAD_CONFIG) {
        renderer.stopThreads();
        if (renderThread.joinable())
            renderThread.join();
        _handleCameraMovement(av);
        return;
    }

    if (renderThread.joinable())
        renderThread.join();

    if (!isProgressiveMode)
        graphicRenderer.switchToFinalImage();
    graphicRenderer.exportToPNG("output.png");
}

RayTracer::Core::Core(char **av, const Math::Point3D &additionalOffset)
:
    _parser(av[1])
{
    const char *offsetXStr = getenv("RAYTRACER_CAMERA_OFFSET_X");
    const char *offsetYStr = getenv("RAYTRACER_CAMERA_OFFSET_Y");
    const char *offsetZStr = getenv("RAYTRACER_CAMERA_OFFSET_Z");

    _cameraOffset = Math::Point3D(0.0, 0.0, 0.0);

    if (offsetXStr && offsetYStr && offsetZStr) {
        try {
            _cameraOffset._x = std::stod(offsetXStr);
            _cameraOffset._y = std::stod(offsetYStr);
            _cameraOffset._z = std::stod(offsetZStr);
        } catch (const std::exception &e) {
        }
    }
    _cameraOffset._x += additionalOffset._x;
    _cameraOffset._y += additionalOffset._y;
    _cameraOffset._z += additionalOffset._z;

    setenv("RAYTRACER_CAMERA_OFFSET_X", std::to_string(_cameraOffset._x).c_str(), 1);
    setenv("RAYTRACER_CAMERA_OFFSET_Y", std::to_string(_cameraOffset._y).c_str(), 1);
    setenv("RAYTRACER_CAMERA_OFFSET_Z", std::to_string(_cameraOffset._z).c_str(), 1);

    this->_loadPlugins();
    this->_sceneElements = RayTracer::Factory::Factory::createElement(
        this->_parser.getCameraConfig(),
        this->_parser.getPrimitivesConfig(),
        this->_parser.getLightConfig(),
        this->_plugins
    );

    auto camera = std::get<2>(this->_sceneElements);
    Math::Point3D currentPos = camera->getPosition();
    camera->setPosition(currentPos._x + _cameraOffset._x,
                       currentPos._y + _cameraOffset._y,
                       currentPos._z + _cameraOffset._z);

    auto renderingConfig = _parser.getRenderingConfig();
    Renderer renderer(this->getCamera(), this->getPrimitives(), this->getLights());
    renderer.setMultithreading(renderingConfig.getMultithreading());
    renderer.setMaxThreads(renderingConfig.getMaxThreads());
    if (renderingConfig.getType() == "preview")
        renderer.renderPreview();

    GraphicRenderer graphicRenderer(
        av[1],
        "preview.ppm",
        "output.ppm",
        renderingConfig.getType() == "preview",
        renderingConfig.getType() == "progressive"
    );
    bool isProgressiveMode = (renderingConfig.getType() == "progressive");

    if (isProgressiveMode) {
        renderer.registerUpdateCallback([&graphicRenderer](
                const std::vector<std::vector<Graphic::color_t>>& pixelBuffer) {
            graphicRenderer.updateProgressiveRendering(pixelBuffer);
        });
    }

    this->applyRenderingConfig(renderer);
    this->applyAntialiasing(renderer);

    std::atomic<bool> renderingComplete(false);

    std::thread renderThread([&]() {
        renderer.render();
        renderingComplete = true;
    });

    runResult_e result = graphicRenderer.run(renderingComplete);

    if (result == RELOAD_CONFIG) {
        renderer.stopThreads();
        if (renderThread.joinable())
            renderThread.join();
        _handleCameraMovement(av);
        return;
    }

    if (renderThread.joinable())
        renderThread.join();

    if (!isProgressiveMode)
        graphicRenderer.switchToFinalImage();
    graphicRenderer.exportToPNG("output.png");
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

void RayTracer::Core::applyAntialiasing(Renderer& renderer) const
{
    auto antialiasingConfig = _parser.getAntialiasingConfig();

    if (antialiasingConfig.getType() == "supersampling") {
        renderer.setAntialiasingMode(Renderer::SUPERSAMPLING);
        renderer.setSupersamplingLevel(antialiasingConfig.getSamples());
    } else if (antialiasingConfig.getType() == "adaptive") {
        renderer.setAntialiasingMode(Renderer::ADAPTIVE_SUPERSAMPLING);
        renderer.setAdaptiveThreshold(antialiasingConfig.getThreshold());
    } else {
        renderer.setAntialiasingMode(Renderer::NONE);
    }
}

void RayTracer::Core::applyRenderingConfig(Renderer& renderer) const
{
    auto renderingConfig = _parser.getRenderingConfig();

    if (renderingConfig.getType() == "progressive") {
        renderer.setRenderingMode(Renderer::PROGRESSIVE);
    } else {
        renderer.setRenderingMode(Renderer::PREVIEW);
    }
}
