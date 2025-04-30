//
// Created by roussierenoa on 5/1/25.
//

#include "Factory.hpp"
#include "PrimitivesFactory/PrimitiveFactory.hpp"

std::tuple<std::vector<std::unique_ptr<IPrimitive>>> raytracer::Factory::Factory::createElement(Parser::CameraConfig &cam,
                                                                               Parser::PrimitivesConfig &primitives,
                                                                               Parser::LightsConfig &light)
{
    std::tuple<std::vector<std::unique_ptr<IPrimitive>>/*Add more data here*/ > result;
    auto data =  raytracer::Factory::PrimitiveFactory::createPrimitives(primitives);

    return result;
}
