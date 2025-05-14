//
// Created by roussierenoa on 4/30/25.
//

#include <iostream>
#include <vector>

#include "LightsConfig.hpp"

namespace RayTracer::Parser {

LightsConfig::LightsConfig(
    const ambient_t &ambient,
    const std::vector<directional_t> &directional,
    const std::vector<point_t> &point
) :
    _directional(directional),
    _ambient(ambient),
    _point(point)
{
}

ambient_t LightsConfig::getAmbient() const {
    return this->_ambient;
}

std::vector<directional_t> LightsConfig::getDirectional() const {
    return this->_directional;
}

std::vector<point_t> LightsConfig::getPoint() const {
    return this->_point;
}
}
