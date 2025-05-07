//
// Created by roussierenoa on 4/30/25.
//

#include "PrimitivesConfig.hpp"

RayTracer::Parser::PrimitivesConfig::PrimitivesConfig(
    const std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &sphere,
    const std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> &plane,
    const std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &cylinders,
    const std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &cone,
    const std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &torus,
    const std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &tanglecube,
    const std::vector<std::tuple<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &triangles,
    const std::vector<std::tuple<std::tuple<double, double, double, std::string>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &obj
):
    _sphere(sphere),
    _cylinders(cylinders),
    _cone(cone),
    _plane(plane),
    _torus(torus),
    _tanglecube(tanglecube),
    _triangles(triangles),
    _obj(obj)
{
}

std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser
::PrimitivesConfig::getCone() const {
    return this->_cone;
}

std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser
::PrimitivesConfig::getCylinders() const {
    return this->_cylinders;
}

std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser::PrimitivesConfig
::getSpheres() const {
    return this->_sphere;
}

std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> RayTracer::Parser::PrimitivesConfig::getPlanes() const {
    return this->_plane;
}

std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser::PrimitivesConfig::getTorus() const {
    return this->_torus;
}

std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> RayTracer::Parser::PrimitivesConfig::getTanglecube() const {
    return this->_tanglecube;
}

std::vector<std::tuple<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>>
RayTracer::Parser::PrimitivesConfig::getTriangles() const {
    return this->_triangles;
}

std::vector<std::tuple<std::tuple<double, double, double, std::string>, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>>
RayTracer::Parser::PrimitivesConfig::getOBJ() const {
    return this->_obj;
}