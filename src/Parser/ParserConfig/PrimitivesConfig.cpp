//
// Created by roussierenoa on 4/30/25.
//

#include "PrimitivesConfig.hpp"

RayTracer::Parser::PrimitivesConfig::PrimitivesConfig(
    const std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> &sphere,
    const std::vector<std::tuple<char, double, std::tuple<int, int, int>>> &plane,
    const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &cylinders,
    const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &cone
):
    _sphere(sphere),
    _cylinders(cylinders),
    _cone(cone),
    _plane(plane)
{
}

std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser
::PrimitivesConfig::getCone() const {
    return this->_cone;
}

std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser
::PrimitivesConfig::getCylinders() const {
    return this->_cylinders;
}

std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser::PrimitivesConfig
::getSpheres() const {
    return this->_sphere;
}

std::vector<std::tuple<char, double, std::tuple<int, int, int>>> RayTracer::Parser::PrimitivesConfig::getPlanes() const {
    return this->_plane;
}