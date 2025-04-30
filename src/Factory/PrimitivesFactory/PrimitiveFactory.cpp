//
// Created by roussierenoa on 5/1/25.
//

#include "PrimitiveFactory.hpp"

std::vector<std::unique_ptr<IPrimitive>> raytracer::Factory::PrimitiveFactory::createPrimitives(
    const raytracer::Parser::PrimitivesConfig &config)
{
    std::vector<std::unique_ptr<IPrimitive>> primitives;

    for (const auto& sphere : config.getSpheres()) {
        auto [posRad, color] = sphere;
        auto [x, y, z, radius] = posRad;
        Math::Point3D pos(x, y, z);

        Raytracer::Factory::SphereFactory factory(pos, radius);
        primitives.emplace_back(factory.create());
    }

    // Planes
    for (const auto& plane : config.getPlanes()) {
        auto [axis, position, color] = plane;
        Math::Point3D pos;
        Math::Vector3D rot;

        if (axis == 'x') {
            pos = Math::Point3D(position, 0, 0);
            rot = Math::Vector3D(0, 0, 90);
        } else if (axis == 'y') {
            pos = Math::Point3D(0, position, 0);
            rot = Math::Vector3D(0, 0, 0);
        } else if (axis == 'z') {
            pos = Math::Point3D(0, 0, position);
            rot = Math::Vector3D(90, 0, 0);
        }

        Raytracer::Factory::PlaneFactory factory(pos, rot);
        primitives.emplace_back(factory.create());
    }

    return primitives;
}
