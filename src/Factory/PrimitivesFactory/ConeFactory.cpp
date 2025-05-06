//
// Created by roussierenoa on 5/1/25.
//

#include "ConeFactory.hpp"
#include "Primitives/Cone/Cone.hpp"

RayTracer::Factory::ConeFactory::ConeFactory(const Math::Point3D &position, double radius, double height):
    _position(position),
    _radius(radius),
    _height(height)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::ConeFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("Cone"))
        throw std::runtime_error("Cone plugin not found");
    auto obj = plugins["Cone"]->initEntryPointPtr<primitive::Cone>("create", this->_position, this->_radius, this->_height);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
