//
// Created by roussierenoa on 4/30/25.
//

#include "LightsConfig.hpp"
#include <iostream>

RayTracer::Parser::LightsConfig::LightsConfig(
const std::tuple<double, std::tuple<int, int, int>> &ambient,
const std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &directional /* Intensité, position, direction, couleur */
):
    _directional(directional),
    _ambient(ambient)
{
}

std::tuple<double, std::tuple<int, int, int>> RayTracer::Parser::LightsConfig::getAmbient() const {
    return this->_ambient;
}

std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int,
int, int>>> RayTracer::Parser::LightsConfig::getDirectional() const {
    return this->_directional;
}
