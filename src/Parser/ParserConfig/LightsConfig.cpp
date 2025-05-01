//
// Created by roussierenoa on 4/30/25.
//

#include "LightsConfig.hpp"

raytracer::Parser::LightsConfig::LightsConfig(
    const std::vector<std::tuple<double, double, double>> &directional,
    const std::tuple<double, double, double> &position,
    const double ambient,
    const double diffuse
):
    _directional(directional),
    _position(position),
    _ambient(ambient),
    _diffuse(diffuse)
{
}

double raytracer::Parser::LightsConfig::getAmbient() const {
    return this->_ambient;
}

double raytracer::Parser::LightsConfig::getDiffuse() const {
    return this->_diffuse;
}

std::tuple<double, double, double> raytracer::Parser::LightsConfig::getPosition() const {
    return this->_position;
}

std::vector<std::tuple<double, double, double>> raytracer::Parser::LightsConfig::getDirectional() const {
    return this->_directional;
}