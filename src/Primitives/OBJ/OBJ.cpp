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
        Math::Point3D min(_vertices[0]);
        Math::Point3D max(_vertices[0]);

        for (const auto &vertex : _vertices) {
            min._x = std::min(min._x, vertex._x);
            min._y = std::min(min._y, vertex._y);
            min._z = std::min(min._z, vertex._z);

            max._x = std::max(max._x, vertex._x);
            max._y = std::max(max._y, vertex._y);
            max._z = std::max(max._z, vertex._z);
        }

        _anchorPoint = Math::Vector3D(
            (max._x + min._x) / 2.0,
            (max._y + min._y) / 2.0,
            (max._z + min._z) / 2.0
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

        v1 = v1 + Math::Vector3D(_position._x, _position._y, _position._z);
        v2 = v2 + Math::Vector3D(_position._x, _position._y, _position._z);
        v3 = v3 + Math::Vector3D(_position._x, _position._y, _position._z);

        try {
            auto triangle = std::make_shared<RayTracer::primitive::Triangles>(v1, v2, v3);
            triangle->setRotation(_rotation);
            _triangles.push_back(triangle);
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

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            double x, y, z;
            if (iss >> x >> y >> z)
                _vertices.emplace_back(x, y, z);
        } else if (type == "f") {
            std::vector<size_t> faceIndices;
            std::string vertex;

            while (iss >> vertex) {
                size_t vertexIdx = std::stoul(vertex.substr(0, vertex.find('/'))) - 1;
                faceIndices.push_back(vertexIdx);
            }
            triangulatePolygon(faceIndices);
        }
    }

    return !_vertices.empty() && !_faces.empty();
}

void OBJ::triangulatePolygon(const std::vector<size_t>& polygonIndices)
{
    if (polygonIndices.size() == 3) {
        _faces.emplace_back(polygonIndices[0], polygonIndices[1], polygonIndices[2]);
        return;
    }
    if (polygonIndices.size() > 3) {
        for (size_t i = 1; i < polygonIndices.size() - 1; ++i) {
            _faces.emplace_back(
                polygonIndices[0],
                polygonIndices[i],
                polygonIndices[i + 1]
            );
        }
    }
}

Math::hitdata_t OBJ::intersect(const Math::Ray &ray)
{
    Math::Ray transformedRay = transformRayToLocal(ray);
    Math::hitdata_t closestHit;

    closestHit.hit = false;
    closestHit.distance = std::numeric_limits<double>::infinity();

    for (const auto &triangle : _triangles) {
        Math::hitdata_t hitData = triangle->intersect(transformedRay);

        if (hitData.hit && hitData.distance < closestHit.distance)
            closestHit = hitData;
    }

    if (closestHit.hit)
        closestHit.color = {255.0, 255.0, 255.0, 1.0};  // White
    return closestHit;
}

}  // namespace RayTracer::primitive
