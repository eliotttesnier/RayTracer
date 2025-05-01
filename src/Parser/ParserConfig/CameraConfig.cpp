//
// Created by roussierenoa on 4/30/25.
//

#include "CameraConfig.hpp"

raytracer::Parser::CameraConfig::CameraConfig(
    const std::tuple<int, int> &resolution,
    const std::tuple<double, double, double> &position,
    const std::tuple<double, double, double> &rotation,
    const double fov
):
    _resolution(resolution),
    _position(position),
    _rotation(rotation),
    _fov(fov)
{
}

std::tuple<int, int> raytracer::Parser::CameraConfig::getResolution() const {
    return this->_resolution;
}

std::tuple<double, double, double> raytracer::Parser::CameraConfig::getPosition() const {
    return this->_position;
}

std::tuple<double, double, double> raytracer::Parser::CameraConfig::getRotation() const {
    return this->_rotation;
}
