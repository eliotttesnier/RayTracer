//
// Created by roussierenoa on 4/30/25.
//

#include "LightsConfig.hpp"
#include <iostream>

namespace RayTracer::Parser {

LightsConfig::LightsConfig(
    const ambient_t &ambient,
    const directional_t &directional
):
    _directional(directional),
    _ambient(ambient)
{
}

ambient_t LightsConfig::getAmbient() const {
    return this->_ambient;
}

directional_t LightsConfig::getDirectional() const {
    return this->_directional;
}

}
