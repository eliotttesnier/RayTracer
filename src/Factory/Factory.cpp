//
// Created by roussierenoa on 5/1/25.
//

#include "Factory.hpp"
#include "PrimitivesFactory/PrimitiveFactory.hpp"

std::tuple<std::vector<std::unique_ptr<IPrimitive>>, std::unique_ptr<RayTracer::Camera>> raytracer::Factory::Factory::createElement(Parser::CameraConfig &camera,
                                                                               Parser::PrimitivesConfig &primitives,
                                                                               Parser::LightsConfig &light)
{
    std::tuple<std::vector<std::unique_ptr<IPrimitive>>, std::unique_ptr<RayTracer::Camera>/*Add more data here*/> result;
    auto primitivesFacto =  raytracer::Factory::PrimitiveFactory::createPrimitives(primitives);
    auto cameraFacto = raytracer::Factory::CameraFactory::createCamera(camera);
    return std::make_tuple(std::move(primitivesFacto), std::move(cameraFacto));
}
