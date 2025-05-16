//
// Created by roussierenoa on 5/1/25.
//

#include "Factory.hpp"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iostream>
#include "LigthsFactory/LightFactory.hpp"
#include "PrimitivesFactory/PrimitiveFactory.hpp"

RayTracer::Factory::scene_t RayTracer::Factory::Factory::createElement(
    const Parser::CameraConfig &camera,
    const Parser::PrimitivesConfig &primitives,
    const Parser::LightsConfig &light,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    #ifdef _DEBUG
        std::cout << std::endl << "Factory running..." << std::endl;
    #endif
    auto primitivesFacto = RayTracer::Factory::PrimitiveFactory::createPrimitives(
        primitives,
        plugins
    );
    auto cameraFacto = RayTracer::Factory::CameraFactory::createCamera(
        camera
    );
    auto lightFacto = RayTracer::Factory::LightFactory::createLights(
        light,
        plugins
    );
    #ifdef _DEBUG
        std::cout << std::endl;
    #endif
    return std::make_tuple(
        std::move(primitivesFacto),
        std::move(lightFacto),
        std::move(cameraFacto)
    );
}
