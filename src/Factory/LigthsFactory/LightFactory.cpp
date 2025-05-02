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

    // const auto &ambient = config.getAmbient();
    // auto [intensity, color] = ambient;
    // auto [r, g, b] = color;
    //
    // //TODO crée la light ici en passsant par le DLLoader
    // RayTracer::light::AmbientLight light;
    // light.setColor(r, g, b);
    // light.setIntensity(intensity);
    // lights.emplace_back(std::make_unique<RayTracer::light::AmbientLight>(light));
    //
    // for (const auto &directional : config.getDirectional()) {
    //     auto [intensity, position, direction, color] = directional;
    //     auto [r, g, b] = color;
    //     auto [px, py, pz] = position;
    //     auto [dx, dy, dz] = direction;
    //
    //     //TODO crée la light ici en passsant par le DLLoader
    //     RayTracer::light::DirectionalLight light;
    //     light.setColor(r, g, b);
    //     light.setIntensity(intensity);
    //     light.setDirection({dx, dy, dz});
    //     light.setPosition(px, py, pz);
    //     lights.emplace_back(std::make_unique<RayTracer::light::DirectionalLight>(light));
    // }

    return lights;
}
