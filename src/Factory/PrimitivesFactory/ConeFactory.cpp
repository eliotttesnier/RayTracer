//
// Created by roussierenoa on 5/1/25.
//

#include <map>
#include <memory>
#include <string>
#include "ConeFactory.hpp"
#include "Primitives/Cone/Cone.hpp"

RayTracer::Factory::ConeFactory::ConeFactory(const Math::Point3D &position,
                                             const Math::Vector3D &rotation,
                                             const Math::Vector3D &scale,
                                             const Math::Vector3D &shear,
                                             double radius, double height):
    _radius(radius),
    _height(height),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::ConeFactory::create(
            std::map<std::string,
            std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("Cone"))
        throw std::runtime_error("Cone plugin not found");
    auto obj = plugins["Cone"]->initEntryPointPtr<primitive::Cone>("create",
                                                                   this->_position,
                                                                   this->_radius,
                                                                   this->_height);
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    obj->setShear(this->_shear);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
