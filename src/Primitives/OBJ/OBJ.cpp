/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** OBJ
*/

#include "OBJ.hpp"

#include <cmath>

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../Triangles/Triangles.hpp"

namespace RayTracer::primitive {

bool AABB::intersect(const Math::Ray &ray) const
{
    double tx1 = (min._x - ray.origin._x) / ray.direction._x;
    double tx2 = (max._x - ray.origin._x) / ray.direction._x;
    double tmin = std::min(tx1, tx2);
    double tmax = std::max(tx1, tx2);

    double ty1 = (min._y - ray.origin._y) / ray.direction._y;
    double ty2 = (max._y - ray.origin._y) / ray.direction._y;
    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    double tz1 = (min._z - ray.origin._z) / ray.direction._z;
    double tz2 = (max._z - ray.origin._z) / ray.direction._z;
    tmin = std::max(tmin, std::min(tz1, tz2));
    tmax = std::min(tmax, std::max(tz1, tz2));

    return tmax >= tmin && tmax > 0;
}

void AABB::expand(const Math::Point3D &point)
{
    min._x = std::min(min._x, point._x);
    min._y = std::min(min._y, point._y);
    min._z = std::min(min._z, point._z);

    max._x = std::max(max._x, point._x);
    max._y = std::max(max._y, point._y);
    max._z = std::max(max._z, point._z);
}

OBJ::OBJ()
{
    _name = "obj";
    _type = "obj";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _filepath = "";
}

OBJ::OBJ(const Math::Point3D &position, const std::string &filepath)
{
    _name = "obj";
    _type = "obj";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _filepath = filepath;
    loadFromFile();
}

const std::string &OBJ::getFilePath() const
{
    return _filepath;
}

void OBJ::loadFromFile()
{
    if (_filepath.empty()) {
        std::cerr << "OBJ: No file path specified" << std::endl;
        return;
    }

    if (!parseOBJFile()) {
        std::cerr << "OBJ: Failed to parse file: " << _filepath << std::endl;
        return;
    }

    if (!_vertices.empty()) {
        _anchorPoint = Math::Vector3D(
            (_boundingBox.min._x + _boundingBox.max._x) / 2.0,
            (_boundingBox.min._y + _boundingBox.max._y) / 2.0,
            (_boundingBox.min._z + _boundingBox.max._z) / 2.0
        );
    }

    for (const auto &face : _faces) {
        size_t idx1 = std::get<0>(face);
        size_t idx2 = std::get<1>(face);
        size_t idx3 = std::get<2>(face);

        if (idx1 >= _vertices.size() ||
            idx2 >= _vertices.size() ||
            idx3 >= _vertices.size()) {
            std::cerr << "OBJ: Invalid face indices" << std::endl;
            continue;
        }

        Math::Point3D v1 = _vertices[idx1];
        Math::Point3D v2 = _vertices[idx2];
        Math::Point3D v3 = _vertices[idx3];
        Math::Point3D transformedV1 = transformVertex(v1);
        Math::Point3D transformedV2 = transformVertex(v2);
        Math::Point3D transformedV3 = transformVertex(v3);

        try {
            auto triangle = std::make_shared<RayTracer::primitive::Triangles>(
                transformedV1, transformedV2, transformedV3);
            _triangles.push_back(triangle);

            AABB triangleBound;
            triangleBound.expand(transformedV1);
            triangleBound.expand(transformedV2);
            triangleBound.expand(transformedV3);
            _triangleBounds.push_back(triangleBound);
        } catch (const std::exception &e) {
            std::cerr << "OBJ: Failed to create triangle: " << e.what() << std::endl;
        }
    }

#ifdef _DEBUG
    std::cout << "OBJ: Loaded " << _triangles.size() << " triangles from "
              << _filepath << std::endl;
#endif
}

bool OBJ::parseOBJFile()
{
    std::ifstream file(_filepath);
    if (!file.is_open()) {
        std::cerr << "OBJ: Could not open file: " << _filepath << std::endl;
        return false;
    }

    _boundingBox = AABB();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            double x, y, z;
            if (iss >> x >> y >> z) {
                Math::Point3D vertex(x, y, z);
                _vertices.emplace_back(vertex);
                _boundingBox.expand(vertex);
            }
        } else if (type == "f") {
            std::vector<size_t> faceIndices;
            std::string vertex;

            while (iss >> vertex) {
                std::istringstream vStream(vertex);
                std::string vPart;
                std::getline(vStream, vPart, '/');

                try {
                    size_t vertexIdx = std::stoul(vPart) - 1;
                    faceIndices.push_back(vertexIdx);
                } catch (const std::exception& e) {
                    std::cerr << "OBJ: Invalid vertex index: " << vPart << std::endl;
                }
            }
            triangulatePolygon(faceIndices);
        }
    }

    return !_vertices.empty() && !_faces.empty();
}

void OBJ::triangulatePolygon(const std::vector<size_t>& polygonIndices)
{
    if (polygonIndices.size() < 3)
        return;

    if (polygonIndices.size() == 3) {
        _faces.emplace_back(polygonIndices[0], polygonIndices[1], polygonIndices[2]);
        return;
    }

    for (size_t i = 1; i < polygonIndices.size() - 1; ++i) {
        _faces.emplace_back(
            polygonIndices[0],
            polygonIndices[i],
            polygonIndices[i + 1]
        );
    }
}

Math::hitdata_t OBJ::intersect(const Math::Ray &ray)
{
    Math::Ray transformedRay = transformRayToLocal(ray);
    Math::hitdata_t closestHit;

    closestHit.hit = false;
    closestHit.distance = std::numeric_limits<double>::infinity();

    if (!_boundingBox.intersect(transformedRay))
        return closestHit;

    for (size_t i = 0; i < _triangles.size(); i++) {
        if (!_triangleBounds[i].intersect(transformedRay))
            continue;

        Math::hitdata_t hitData = _triangles[i]->intersect(transformedRay);
        if (hitData.hit && hitData.distance < closestHit.distance)
            closestHit = hitData;
    }

    if (closestHit.hit)
        closestHit.color = {255.0, 255.0, 255.0, 1.0};  // White
    return closestHit;
}

Math::Point3D OBJ::transformVertex(const Math::Point3D& vertex)
{
    Math::Point3D result = vertex;
    double cosX = std::cos(_rotation._x * M_PI / 180.0);
    double sinX = std::sin(_rotation._x * M_PI / 180.0);
    double cosY = std::cos(_rotation._y * M_PI / 180.0);
    double sinY = std::sin(_rotation._y * M_PI / 180.0);
    double cosZ = std::cos(_rotation._z * M_PI / 180.0);
    double sinZ = std::sin(_rotation._z * M_PI / 180.0);

    result = result - Math::Vector3D(_anchorPoint._x, _anchorPoint._y, _anchorPoint._z);
    rotatePointToWorld(result, cosX, sinX, cosY, sinY, cosZ, sinZ);
    result = result + Math::Vector3D(_anchorPoint._x, _anchorPoint._y, _anchorPoint._z);
    result = result + Math::Vector3D(_position._x, _position._y, _position._z);

    return result;
}

}  // namespace RayTracer::primitive
