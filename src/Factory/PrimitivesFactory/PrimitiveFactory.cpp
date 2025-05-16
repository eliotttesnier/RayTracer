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
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
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

    auto rectangles = _addRectangles(config, plugins);
    primitives.insert(primitives.end(), rectangles.begin(), rectangles.end());

    // FractaleCubes
    for (const auto &fractalecube : config.getFractaleCubes()) {
        auto [shading, materials, size, recursion, position, rotation, sc, sh, color] =
            fractalecube;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::FractaleCubeFactory factory(
            shading,
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
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }

    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addSpheres(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &sphere : config.getSpheres()) {
        auto [shading, materials, radius, position, rotation, sc, sh, color] = sphere;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::SphereFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            radius,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a sphere... " << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addPlanes(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &plane : config.getPlanes()) {
        auto [shading, materials, axis, position, rotation, sc, sh, color] = plane;
        Math::Point3D pos = position;
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::PlaneFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a plane" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addCylinders(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cylinder : config.getCylinders()) {
        auto [shading, materials, size, position, rotation, sc, sh, color] = cylinder;
        auto [radius, height] = size;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::CylinderFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            radius,
            height,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a cylinder" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addCones(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cone : config.getCones()) {
        auto [shading, materials, size, position, rotation, sc, sh, color] = cone;
        auto [radius, height] = size;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::ConeFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            radius,
            height,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a cone" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addToruses(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &torus : config.getToruses()) {
        auto [shading, materials, radius, position, rotation, sc, sh, color] = torus;
        auto [majorRadius, minorRadius] = radius;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::TorusFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            majorRadius,
            minorRadius,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a torus" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addTanglecubes(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &tanglecube : config.getTanglecubes()) {
        auto [shading, materials, size, position, rotation, sc, sh, color] = tanglecube;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::TanglecubeFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            size,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a tanglecube" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addTriangles(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &triangle : config.getTriangles()) {
        auto [shading, materials, points, rotation, sc, sh, color] = triangle;
        auto [p1, p2, p3] = points;
        Math::Point3D point1 = p1;
        Math::Point3D point2 = p2;
        Math::Point3D point3 = p3;
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::TrianglesFactory factory(
            shading,
            point1,
            point2,
            point3,
            rota,
            scale,
            shear,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a triangle" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addOBJs(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &obj : config.getOBJs()) {
        auto [shading, materials, filepath, position, rotation, sc, sh, color] = obj;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::OBJFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            filepath,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating an OBJ object from file: " << filepath << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addInfiniteCones(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cone : config.getInfiniteCones()) {
        auto [shading, materials, angle, position, rotation, sc, sh, color] = cone;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        RayTracer::Factory::InfiniteConeFactory factory(
            shading,
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
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addInfiniteCylinders(
    const RayTracer::Parser::PrimitivesConfig &config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &cylinder : config.getInfiniteCylinders()) {
        auto [shading, materials, radius, position, rotation, sc, sh, color] = cylinder;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;
        RayTracer::Factory::InfiniteCylinderFactory factory(
            shading,
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
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

std::vector<std::shared_ptr<IPrimitive>> PrimitiveFactory::_addRectangles(
    const RayTracer::Parser::PrimitivesConfig& config,
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<IPrimitive>> primitives;
    for (const auto &rectangle : config.getRectangles()) {
        auto [shading, materials, dimensions, position, rotation, sc, sh, color] = rectangle;
        auto [length, width, height] = dimensions;
        auto [x, y, z] = position;
        Math::Point3D pos(x, y, z);
        Math::Vector3D rota = rotation;
        Math::Vector3D scale = sc;
        Math::Vector3D shear = sh;

        RayTracer::Factory::RectangleFactory factory(
            shading,
            pos,
            rota,
            scale,
            shear,
            length,
            width,
            height,
            materials
        );
        #ifdef _DEBUG
            std::cout << "Creating a rectangle" << std::endl;
        #endif
        auto primitive = factory.create(plugins);
        auto [r, g, b] = color;
        primitive->setColor(Graphic::color_t{static_cast<double>(r), static_cast<double>(g),
            static_cast<double>(b), 1.0});
        primitives.emplace_back(primitive);
    }
    return primitives;
}

}
