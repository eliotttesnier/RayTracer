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
        auto [posRad, sc, color] = sphere;
        auto [x, y, z, radius] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D scale;
        scale = sc;

        RayTracer::Factory::SphereFactory factory(pos, scale, radius);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a sphere... " << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Planes
    for (const auto& plane : config.getPlanes()) {
        auto [axis, position, rotation, sc, size, color] = plane;
        Math::Point3D pos;
        Math::Vector3D rota;
        Math::Vector3D scale;
        pos = position;
        rota = rotation;
        scale = sc;

        RayTracer::Factory::PlaneFactory factory(pos, rota, scale, size);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a plane" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Cylinders
    for (const auto& cylinder : config.getCylinders()) {
        auto [posRad, rotation, sc, color] = cylinder;
        auto [x, y, z, radius, height] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota;
        Math::Vector3D scale;
        rota = rotation;
        scale = sc;

        RayTracer::Factory::CylinderFactory factory(pos, rota, scale, radius, height);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a cylinder" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Cone
    for (const auto &cone : config.getCone()) {
        auto [posRad, rotation, sc, color] = cone;
        auto [x, y, z, radius, height] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota;
        Math::Vector3D scale;
        rota = rotation;
        scale = sc;

        RayTracer::Factory::ConeFactory factory(pos, rota, scale, radius, height);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a cone" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Torus
    for (const auto &torus : config.getTorus()) {
        auto [posRad, rotation, sc, color] = torus;
        auto [x, y, z, majorRadius, minorRadius] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota;
        Math::Vector3D scale;
        rota = rotation;
        scale = sc;

        RayTracer::Factory::TorusFactory factory(pos, rota, scale, majorRadius, minorRadius);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a torus" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Tanglecube
    for (const auto &tanglecube : config.getTanglecube()) {
        auto [posSize, rotation, sc, color] = tanglecube;
        auto [x, y, z, size] = posSize;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota;
        Math::Vector3D scale;
        rota = rotation;
        scale = sc;

        RayTracer::Factory::TanglecubeFactory factory(pos, rota, scale, size);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a tanglecube" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Triangles
    for (const auto &triangle : config.getTriangles()) {
        auto [points, rotation, sc, color] = triangle;
        auto [p1, p2, p3] = points;
        Math::Point3D point1;
        Math::Point3D point2;
        Math::Point3D point3;
        Math::Vector3D rota;
        Math::Vector3D scale;
        point1 = p1;
        point2 = p2;
        point3 = p3;
        rota = rotation;
        scale = sc;

        RayTracer::Factory::TrianglesFactory factory(point1, point2, point3, rota, scale);
#ifdef _DEBUG
        std::cout << "Creating a triangle" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // OBJ files
    for (const auto &obj : config.getOBJ()) {
        auto [posPath, rotation, sc, color] = obj;
        auto [x, y, z, filepath] = posPath;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota;
        Math::Vector3D scale;
        rota = rotation;
        scale = sc;


        RayTracer::Factory::OBJFactory factory(pos, rota, scale, filepath);
#ifdef _DEBUG
        std::cout << "Creating an OBJ object from file: " << filepath << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    return primitives;
}
