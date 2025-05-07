//
// Created by roussierenoa on 5/1/25.
//

#include <iostream>
#include "PrimitiveFactory.hpp"
#include "PlaneFactory.hpp"
#include "SphereFactory.hpp"
#include "CylinderFactory.hpp"
#include "ConeFactory.hpp"
#include "TorusFactory.hpp"
#include "TanglecubeFactory.hpp"
#include "TrianglesFactory.hpp"
#include "OBJFactory.hpp"

std::vector<std::shared_ptr<IPrimitive>> RayTracer::Factory::PrimitiveFactory::createPrimitives(
    const RayTracer::Parser::PrimitivesConfig &config, std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;

    for (const auto& sphere : config.getSpheres()) {
        auto [posRad, color] = sphere;
        auto [x, y, z, radius] = posRad;
        Math::Point3D pos(x, y, z);

        RayTracer::Factory::SphereFactory factory(pos, radius);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a sphere... " << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Planes
    for (const auto& plane : config.getPlanes()) {
        auto [axis, position, rotation, size, color] = plane;
        auto [x, y, z] = position;
        auto [rx, ry, rz] = rotation;
        Math::Point3D pos = Math::Point3D(x, y, z);
        Math::Vector3D rot = Math::Vector3D(rx, ry, rz);

        RayTracer::Factory::PlaneFactory factory(pos, rot, size);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a plane" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Cylinders
    for (const auto& cylinder : config.getCylinders()) {
        auto [posRad, rotation, color] = cylinder;
        auto [x, y, z, radius, height] = posRad;
        auto [rx, ry, rz] = rotation;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota(rx, ry, rz);

        RayTracer::Factory::CylinderFactory factory(pos, rota, radius, height);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a cylinder" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Cone
    for (const auto &cone : config.getCone()) {
        auto [posRad, rotation, color] = cone;
        auto [x, y, z, radius, height] = posRad;
        auto [rx, ry, rz] = rotation;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota(rx, ry, rz);

        RayTracer::Factory::ConeFactory factory(pos, rota, radius, height);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a cone" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Torus
    for (const auto &torus : config.getTorus()) {
        auto [posRad, rotation, color] = torus;
        auto [x, y, z, majorRadius, minorRadius] = posRad;
        auto [rx, ry, rz] = rotation;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota(rx, ry, rz);

        RayTracer::Factory::TorusFactory factory(pos, rota, majorRadius, minorRadius);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a torus" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Tanglecube
    for (const auto &tanglecube : config.getTanglecube()) {
        auto [posSize, rotation, color] = tanglecube;
        auto [x, y, z, size] = posSize;
        auto [rx, ry, rz] = rotation;
            Math::Point3D pos(x, y, z);
        Math::Vector3D rota(rx, ry, rz);

        RayTracer::Factory::TanglecubeFactory factory(pos, rota, size);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a tanglecube" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Triangles
    for (const auto &triangle : config.getTriangles()) {
        auto [points, rotation, color] = triangle;
        auto [p1, p2, p3] = points;
        auto [rx, ry, rz] = rotation;
        Math::Point3D point1(std::get<0>(p1), std::get<1>(p1), std::get<2>(p1));
        Math::Point3D point2(std::get<0>(p2), std::get<1>(p2), std::get<2>(p2));
        Math::Point3D point3(std::get<0>(p3), std::get<1>(p3), std::get<2>(p3));
        Math::Vector3D rota(rx, ry, rz);

        RayTracer::Factory::TrianglesFactory factory(point1, point2, point3, rota);
#ifdef _DEBUG
        std::cout << "Creating a triangle" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // OBJ files
    for (const auto &obj : config.getOBJ()) {
        auto [posPath, rotation, color] = obj;
        auto [x, y, z, filepath] = posPath;
        auto [rx, ry, rz] = rotation;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota(rx, ry, rz);

        RayTracer::Factory::OBJFactory factory(pos, rota, filepath);
#ifdef _DEBUG
        std::cout << "Creating an OBJ object from file: " << filepath << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    return primitives;
}
