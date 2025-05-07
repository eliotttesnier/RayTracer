/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** OBJ
*/

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include "OBJ.hpp"
#include "../Triangles/Triangles.hpp"

namespace RayTracer::primitive {

OBJ::OBJ()
{
    _name = "obj";
    _type = "obj";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _filepath = "";
}

OBJ::OBJ(const Math::Point3D &position, const std::string &filepath)
{
    _name = "obj";
    _type = "obj";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
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

    for (const auto &face : _faces) {
        size_t idx1 = std::get<0>(face);
        size_t idx2 = std::get<1>(face);
        size_t idx3 = std::get<2>(face);

        if (idx1 >= _vertices.size() || idx2 >= _vertices.size() || idx3 >= _vertices.size()) {
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
            _triangles.push_back(triangle);
        } catch (const std::exception &e) {
            std::cerr << "OBJ: Failed to create triangle: " << e.what() << std::endl;
        }
    }

#ifdef _DEBUG
    std::cout << "OBJ: Loaded " << _triangles.size() << " triangles from " << _filepath << std::endl;
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
    Math::hitdata_t closestHit;
    closestHit.hit = false;
    closestHit.distance = std::numeric_limits<double>::infinity();

    for (const auto &triangle : _triangles) {
        Math::hitdata_t hitData = triangle->intersect(ray);

        if (hitData.hit && hitData.distance < closestHit.distance)
            closestHit = hitData;
    }

    if (closestHit.hit)
        closestHit.color = {255.0, 255.0, 255.0, 1.0};  // White
    return closestHit;
}

} // namespace RayTracer::primitive
