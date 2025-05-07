//
// Created by roussierenoa on 4/30/25.
//

#include "LightsConfig.hpp"
#include <iostream>

namespace RayTracer::Parser {

LightsConfig::LightsConfig(
    const ambient_t &ambient,
    const std::vector<directional_t> &directional
):
    _directional(directional),
    _ambient(ambient)
{
}

ambient_t LightsConfig::getAmbient() const {
    return this->_ambient;
}

std::vector<directional_t> LightsConfig::getDirectional() const {
    return this->_directional;
}

}
