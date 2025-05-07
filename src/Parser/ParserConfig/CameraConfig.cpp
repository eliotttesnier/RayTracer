//
// Created by roussierenoa on 4/30/25.
//

#include "CameraConfig.hpp"
#include <tuple>

RayTracer::Parser::CameraConfig::CameraConfig(
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

std::tuple<int, int> RayTracer::Parser::CameraConfig::getResolution() const {
    return this->_resolution;
}

std::tuple<double, double, double> RayTracer::Parser::CameraConfig::getPosition() const {
    return this->_position;
}

std::tuple<double, double, double> RayTracer::Parser::CameraConfig::getRotation() const {
    return this->_rotation;
}

double RayTracer::Parser::CameraConfig::getFov() const {
    return this->_fov;
}
