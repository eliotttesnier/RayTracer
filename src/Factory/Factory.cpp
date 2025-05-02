//
// Created by roussierenoa on 5/1/25.
//

#include "Factory.hpp"

#include "LigthsFactory/LightFactory.hpp"
#include "PrimitivesFactory/PrimitiveFactory.hpp"

std::tuple<std::vector<std::unique_ptr<IPrimitive>>, std::vector<std::unique_ptr<ILight>>, std::unique_ptr<RayTracer::Camera>> RayTracer::Factory::Factory::createElement(const Parser::CameraConfig &camera,
                                                                               const Parser::PrimitivesConfig &primitives,
                                                                               const Parser::LightsConfig &light,
                                                                               std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins)
{
    std::tuple<std::vector<std::unique_ptr<IPrimitive>>, std::unique_ptr<RayTracer::Camera>/*Add more data here*/> result;
    auto primitivesFacto =  RayTracer::Factory::PrimitiveFactory::createPrimitives(primitives);
    auto cameraFacto = RayTracer::Factory::CameraFactory::createCamera(camera);
    auto lightFacto = RayTracer::Factory::LightFactory::createLights(light, plugins);
    return std::make_tuple(std::move(primitivesFacto), std::move(lightFacto), std::move(cameraFacto));
}
