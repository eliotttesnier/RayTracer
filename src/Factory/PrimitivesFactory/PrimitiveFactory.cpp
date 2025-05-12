//
// Created by roussierenoa on 5/1/25.
//

#include "PrimitiveFactory.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "PlaneFactory.hpp"
#include "SphereFactory.hpp"
#include "CylinderFactory.hpp"
#include "ConeFactory.hpp"
#include "TorusFactory.hpp"
#include "TanglecubeFactory.hpp"
#include "TrianglesFactory.hpp"
#include "OBJFactory.hpp"
#include "FractaleCubeFactory.hpp"

namespace RayTracer::Factory {

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::createPrimitives(
    const RayTracer::Parser::PrimitivesConfig &config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;

    auto spheres = _addSpheres(config, plugins);
    primitives.insert(primitives.end(), spheres.begin(), spheres.end());

    auto planes = _addPlanes(config, plugins);
    primitives.insert(primitives.end(), planes.begin(), planes.end());

    auto cylinders = _addCylinders(config, plugins);
    primitives.insert(primitives.end(), cylinders.begin(), cylinders.end());

    auto cones = _addCones(config, plugins);
    primitives.insert(primitives.end(), cones.begin(), cones.end());

    auto toruses = _addToruses(config, plugins);
    primitives.insert(primitives.end(), toruses.begin(), toruses.end());

    auto tanglecubes = _addTanglecubes(config, plugins);
    primitives.insert(primitives.end(), tanglecubes.begin(), tanglecubes.end());

    auto triangles = _addTriangles(config, plugins);
    primitives.insert(primitives.end(), triangles.begin(), triangles.end());

    auto objs = _addOBJs(config, plugins);
    primitives.insert(primitives.end(), objs.begin(), objs.end());

    auto infiniteCones = _addInfiniteCones(config, plugins);
    primitives.insert(primitives.end(), infiniteCones.begin(), infiniteCones.end());

    auto infiniteCylinders = _addInfiniteCylinders(config, plugins);
    primitives.insert(primitives.end(), infiniteCylinders.begin(), infiniteCylinders.end());
    // FractaleCubes
    for (const auto &fractalecube : config.getFractaleCubes()) {
        auto [materials, posSize, rotation, sc, sh, color] = fractalecube;
        auto [x, y, z, size, recursion] = posSize;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::FractaleCubeFactory factory(
            pos,
            rota,
            scale,
            shear,
            size,
            recursion,
            materials
        );
#ifdef _DEBUG
        std::cout << "Creating a fractale cube" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addSpheres(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto& sphere : config.getSpheres()) {
        auto [materials, posRad, rotation, sc, sh, color] = sphere;
        auto [x, y, z, radius] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::SphereFactory factory(
            pos,
            rota,
            scale,
            shear,
            radius,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a sphere... " << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addPlanes(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto& plane : config.getPlanes()) {
        auto [materials, axis, position, rotation, sc, sh, color] = plane;
        Math::Point3D pos = position;
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::PlaneFactory factory(
            pos,
            rota,
            scale,
            shear,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a plane" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addCylinders(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto& cylinder : config.getCylinders()) {
        auto [materials, posRad, rotation, sc, sh, color] = cylinder;
        auto [x, y, z, radius, height] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::CylinderFactory factory(
            pos,
            rota,
            scale,
            shear,
            radius,
            height,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a cylinder" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addCones(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cone : config.getCones()) {
        auto [materials, posRad, rotation, sc, sh, color] = cone;
        auto [x, y, z, radius, height] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::ConeFactory factory(
            pos,
            rota,
            scale,
            shear,
            radius,
            height,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a cone" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addToruses(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &torus : config.getToruses()) {
        auto [materials, posRad, rotation, sc, sh, color] = torus;
        auto [x, y, z, majorRadius, minorRadius] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::TorusFactory factory(
            pos,
            rota,
            scale,
            shear,
            majorRadius,
            minorRadius,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a torus" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addTanglecubes(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &tanglecube : config.getTanglecubes()) {
        auto [materials, posSize, rotation, sc, sh, color] = tanglecube;
        auto [x, y, z, size] = posSize;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::TanglecubeFactory factory(
            pos,
            rota,
            scale,
            shear,
            size,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a tanglecube" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addTriangles(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &triangle : config.getTriangles()) {
        auto [materials, points, rotation, sc, sh, color] = triangle;
        auto [p1, p2, p3] = points;
        Math::Point3D point1 = p1;
        Math::Point3D point2 = p2;
        Math::Point3D point3 = p3;
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::TrianglesFactory factory(
            point1,
            point2,
            point3,
            rota,
            scale,
            shear,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating a triangle" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addOBJs(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &obj : config.getOBJs()) {
        auto [materials, posPath, rotation, sc, sh, color] = obj;
        auto [x, y, z, filepath] = posPath;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        Math::Vector3D mat = materials;
        RayTracer::Factory::OBJFactory factory(
            pos,
            rota,
            scale,
            shear,
            filepath,
            mat
        );
        #ifdef _DEBUG
            std::cout << "Creating an OBJ object from file: " << filepath << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addInfiniteCones(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cone : config.getInfiniteCones()) {
        auto [materials, posAng, rotation, sc, sh, color] = cone;
        auto [x, y, z, angle] = posAng;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        RayTracer::Factory::InfiniteConeFactory factory(
            pos,
            rota,
            scale,
            shear,
            angle,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating an infinite cone" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addInfiniteCylinders(
    const RayTracer::Parser::PrimitivesConfig& config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cylinder : config.getInfiniteCylinders()) {
        auto [materials, posRad, rotation, sc, sh, color] = cylinder;
        auto [x, y, z, radius] = posRad;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        RayTracer::Factory::InfiniteCylinderFactory factory(
            pos,
            rota,
            scale,
            shear,
            radius,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating an infinite cylinder" << std::endl;
        #endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}

}
