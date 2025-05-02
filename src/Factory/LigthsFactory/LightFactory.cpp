//
// Created by roussierenoa on 5/1/25.
//

#include "LightFactory.hpp"

#include "Lights/AmbientLight/AmbientLight.hpp"
#include "Lights/DirectionalLight/DirectionalLight.hpp"


std::vector<std::unique_ptr<ILight>> RayTracer::Factory::LightFactory::createLights(
    const RayTracer::Parser::LightsConfig &config, std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins)
{
    std::vector<std::unique_ptr<ILight>> lights;

    const auto &ambient = config.getAmbient();
    auto [intensity, color] = ambient;
    auto [r, g, b] = color;

    if (!plugins.contains("AmbientLight"))
        throw std::runtime_error("AmbientLight plugin not found");
    auto obj = plugins["AmbientLight"]->initEntryPointPtr<light::AmbientLight>("create");
    obj->setColor(r, g, b);
    obj->setIntensity(intensity);
    lights.emplace_back(obj);

    for (const auto &directional : config.getDirectional()) {
        auto [intensity, position, direction, color] = directional;
        auto [r, g, b] = color;
        auto [px, py, pz] = position;
        auto [dx, dy, dz] = direction;

        if (!plugins.contains("DirectionalLight"))
            throw std::runtime_error("DirectionalLight plugin not found");
        auto obj = plugins["DirectionalLight"]->initEntryPointPtr<light::DirectionalLight>("create");
        obj->setColor(r, g, b);
        obj->setIntensity(intensity);
        obj->setDirection({dx, dy, dz});
        obj->setPosition(px, py, pz);
        lights.emplace_back(obj);
    }

    return lights;
}
