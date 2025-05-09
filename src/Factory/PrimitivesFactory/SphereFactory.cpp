//
// Created by roussierenoa on 5/1/25.
//

#include "SphereFactory.hpp"

#include <map>
#include <memory>
#include <string>

#include "Primitives/Sphere/Sphere.hpp"

RayTracer::Factory::SphereFactory::SphereFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double radius):
    _radius(radius),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::SphereFactory::create(
            std::map<std::string,
            std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("Sphere"))
        throw std::runtime_error("Sphere plugin not found");
    auto obj = plugins["Sphere"]->initEntryPointPtr<primitive::Sphere>(
        "create",
        this->_position,
        this->_radius
    );
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    obj->setShear(this->_shear);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
