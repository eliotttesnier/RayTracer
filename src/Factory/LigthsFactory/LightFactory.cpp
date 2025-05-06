//
// Created by roussierenoa on 5/1/25.
//

#include <iostream>
#include "LightFactory.hpp"

#include "AmbientFactory.hpp"
#include "DirectionalFactory.hpp"
#include "Lights/AmbientLight/AmbientLight.hpp"
#include "Lights/DirectionalLight/DirectionalLight.hpp"

std::vector<std::shared_ptr<ILight>> RayTracer::Factory::LightFactory::createLights(
    const RayTracer::Parser::LightsConfig &config, std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins)
{
    std::vector<std::shared_ptr<ILight>> lights;

    const auto &ambient = config.getAmbient();
    auto [intensity, color] = ambient;
    AmbientFactory factory  = AmbientFactory(intensity, color);
#ifdef _DEBUG
    std::cout << "Creating a ambient light" << std::endl;
#endif
    lights.emplace_back(factory.create(plugins));

    for (const auto &directional : config.getDirectional()) {
        auto [intensity, position, direction, color] = directional;
        DirectionalFactory factory  = DirectionalFactory(intensity, position, direction, color);
#ifdef _DEBUG
        std::cout << "Creating a directional light" << std::endl;
#endif
        lights.emplace_back(factory.create(plugins));
    }
    return lights;
}
