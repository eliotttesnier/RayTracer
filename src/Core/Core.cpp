//
// Created by roussierenoa on 5/2/25.
//

#include "Core.hpp"
#include <iostream>
#include <filesystem>
#include <string>

#include "Factory/Factory.hpp"
#include "Parser/Parser.hpp"

void RayTracer::Core::_loadPlugins()
{
    try {
        std::string pluginDir = "./plugins";
        if (!std::filesystem::exists("./plugins") || !std::filesystem::is_directory("./plugins")) {
            std::cerr << "Plugin directory doesn't exist or is not a directory: ./plugins" << std::endl;
            return;
        }
#ifdef _DEBUG
        std::cout << std::endl << "Loading plugins..." << std::endl;
#endif

        for (const auto &entry : std::filesystem::directory_iterator(pluginDir)) {
            std::string path = entry.path().string();
            if (path.substr(path.find_last_of(".") + 1) == "so") {
                std::string name = path.substr(path.find_last_of("/") + 1);
                name = name.substr(3, name.length() - 6);
                this->_plugins[name] = std::make_unique<Loader::LibLoader>();
                this->_plugins[name]->openLib(path);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading plugins: " << e.what() << std::endl;
    }
}

RayTracer::Core::Core(char **av
):
    _parser(av[1])
{
    this->_loadPlugins();
    this->_sceneElements = RayTracer::Factory::Factory::createElement(this->_parser.getCameraConfig(),
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
