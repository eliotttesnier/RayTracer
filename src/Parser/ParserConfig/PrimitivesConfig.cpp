//
// Created by roussierenoa on 4/30/25.
//

#include <vector>

#include "PrimitivesConfig.hpp"

namespace RayTracer::Parser {

PrimitivesConfig::PrimitivesConfig(
    const std::vector<sphere_t> &spheres,
    const std::vector<plane_t> &planes,
    const std::vector<cylinder_t> &cylinders,
    const std::vector<cone_t> &cones,
    const std::vector<torus_t> &toruses,
    const std::vector<tanglecube_t> &tanglecubes,
    const std::vector<triangle_t> &triangles,
    const std::vector<obj_t> &objs
) :
_spheres(spheres),
_cylinders(cylinders),
_cones(cones),
_planes(planes),
_toruses(toruses),
_tanglecubes(tanglecubes),
_triangles(triangles),
_objs(objs)
{
}

std::vector<cone_t> PrimitivesConfig::getCones() const {
    return this->_cones;
}

std::vector<cylinder_t> PrimitivesConfig::getCylinders() const {
    return this->_cylinders;
}

std::vector<sphere_t> PrimitivesConfig::getSpheres() const {
    return this->_spheres;
}

std::vector<plane_t> PrimitivesConfig::getPlanes() const {
    return this->_planes;
}

std::vector<torus_t> PrimitivesConfig::getToruses() const {
    return this->_toruses;
}

std::vector<tanglecube_t> PrimitivesConfig::getTanglecubes() const {
    return this->_tanglecubes;
}

std::vector<triangle_t> PrimitivesConfig::getTriangles() const {
    return this->_triangles;
}

std::vector<obj_t> PrimitivesConfig::getOBJs() const {
    return this->_objs;
}

}
