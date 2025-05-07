//
// Created by roussierenoa on 5/1/25.
//

#include "CylinderFactory.hpp"

#include <map>
#include <memory>
#include <string>

#include "Primitives/Cylinder/Cylinder.hpp"

// TODO(roussierenoa): Utiliser Libloader pour charger les primitives

RayTracer::Factory::CylinderFactory::CylinderFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            double radius,
            double height):
    _radius(radius),
    _height(height),
    _position(position),
    _rotation(rotation),
    _scale(scale)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::CylinderFactory::create(
            std::map<std::string,
            std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("Cylinder"))
        throw std::runtime_error("Cylinder plugin not found");
    auto obj = plugins["Cylinder"]->initEntryPointPtr<primitive::Cylinder>(
        "create",
        this->_position,
        this->_radius,
        this->_height
    );
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
