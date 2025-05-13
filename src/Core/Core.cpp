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

RayTracer::Core::Core(char **av
):
    _parser(av[1])
{
    this->_loadPlugins();
    this->_sceneElements = RayTracer::Factory::Factory::createElement(
                                 this->_parser.getCameraConfig(),
                                 this->_parser.getPrimitivesConfig(),
                                 this->_parser.getLightConfig(),
                                 this->_plugins);
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
