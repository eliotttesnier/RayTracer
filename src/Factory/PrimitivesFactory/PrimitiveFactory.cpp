//
// Created by roussierenoa on 5/1/25.
//

#include <iostream>
#include "PrimitiveFactory.hpp"
#include "PlaneFactory.hpp"
#include "SphereFactory.hpp"
#include "CylinderFactory.hpp"
#include "ConeFactory.hpp"

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
        auto [axis, position, size, color] = plane;
        Math::Point3D pos = Math::Point3D(std::get<0>(position), std::get<1>(position), std::get<2>(position));;
        Math::Vector3D rot = Math::Vector3D(0, 0, 0);

        RayTracer::Factory::PlaneFactory factory(pos, rot, size);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a plane" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Cylinders
    for (const auto& cylinder : config.getCylinders()) {
        auto [posRad, color] = cylinder;
        auto [x, y, z, radius, height] = posRad;
        Math::Point3D pos(x, y, z);

        RayTracer::Factory::CylinderFactory factory(pos, radius, height);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a cylinder" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }

    // Cone
    for (const auto &cone : config.getCone()) {
        auto [posRad, color] = cone;
        auto [x, y, z, radius, height] = posRad;
        Math::Point3D pos(x, y, z);

        RayTracer::Factory::ConeFactory factory(pos, radius, height);
        // TODO: faire passer dans l'élément dans un design pattern pour ajouter un matériaux
#ifdef _DEBUG
        std::cout << "Creating a cone" << std::endl;
#endif
        primitives.emplace_back(factory.create(plugins));
    }
    return primitives;
}
