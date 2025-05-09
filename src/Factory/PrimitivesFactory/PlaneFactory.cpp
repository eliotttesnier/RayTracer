//
// Created by roussierenoa on 5/1/25.
//

#include "PlaneFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "Primitives/Plane/Plane.hpp"

RayTracer::Factory::PlaneFactory::PlaneFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const std::tuple<double, double> &size):
    _size(size),
    _position(position),
    _rotation(rotation),
    _scale(scale)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::PlaneFactory::create(
            std::map<std::string,
            std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("Plane"))
        throw std::runtime_error("Plane plugin not found");
    auto obj = plugins["Plane"]->initEntryPointPtr<primitive::Plane>(
        "create",
        this->_position,
        this->_rotation,
        this->_size
    );
    obj->setScale(this->_scale);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
