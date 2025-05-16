//
// Created by roussierenoa on 5/1/25.
//

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "LightFactory.hpp"

#include "AmbientFactory.hpp"
#include "DirectionalFactory.hpp"
#include "PointFactory.hpp"
#include "Lights/AmbientLight/AmbientLight.hpp"
#include "Lights/DirectionalLight/DirectionalLight.hpp"

std::vector<std::shared_ptr<ILight>> RayTracer::Factory::LightFactory::createLights(
    const RayTracer::Parser::LightsConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins)
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
        DirectionalFactory factory  = DirectionalFactory(
            intensity,
            position,
            direction,
            color
        );
        #ifdef _DEBUG
                std::cout << "Creating a directional light" << std::endl;
        #endif
        lights.emplace_back(factory.create(plugins));
    }

    for (const auto &point : config.getPoint()) {
        auto [intensity, position, color] = point;
        PointFactory factory  = PointFactory(intensity, position, color);
        lights.emplace_back(factory.create(plugins));
        #ifdef _DEBUG
                std::cout << "Creating a point light" << std::endl;
        #endif
    }

    return lights;
}
