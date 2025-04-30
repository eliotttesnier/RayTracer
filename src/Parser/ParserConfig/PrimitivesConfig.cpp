//
// Created by roussierenoa on 4/30/25.
//

#include "PrimitivesConfig.hpp"

raytracer::Parser::PrimitivesConfig::PrimitivesConfig(
    const std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> &sphere,
    const std::vector<std::tuple<char, double, std::tuple<int, int, int>>> &plane
):
    _sphere(sphere),
    _plane(plane)
{
}

std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> raytracer::Parser::PrimitivesConfig
::getSpheres() const {
    return this->_sphere;
}

std::vector<std::tuple<char, double, std::tuple<int, int, int>>> raytracer::Parser::PrimitivesConfig::getPlanes() const {
    return this->_plane;
}