//
// Created by roussierenoa on 4/30/25.
//

#include "CameraConfig.hpp"
#include <tuple>

namespace RayTracer::Parser {

CameraConfig::CameraConfig(
const resolution_t &resolution,
const truple_t &position,
const truple_t &rotation,
const double fov
):
_resolution(resolution),
_position(position),
_rotation(rotation),
_fov(fov)
{
}

resolution_t CameraConfig::getResolution() const {
    return this->_resolution;
}

truple_t CameraConfig::getPosition() const {
    return this->_position;
}

truple_t CameraConfig::getRotation() const {
    return this->_rotation;
}

double RayTracer::Parser::CameraConfig::getFov() const {
    return this->_fov;
}

}
