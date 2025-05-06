//
// Created by roussierenoa on 5/1/25.
//

#include "CylinderFactory.hpp"

#include "Primitives/Cylinder/Cylinder.hpp"

//TODO: Utiliser Libloader pour charger les primitives

RayTracer::Factory::CylinderFactory::CylinderFactory(const Math::Point3D &position, double radius, double height):
    _position(position),
    _radius(radius),
    _height(height)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::CylinderFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("Cylinder"))
        throw std::runtime_error("Cylinder plugin not found");
    auto obj = plugins["Cylinder"]->initEntryPointPtr<primitive::Cylinder>("create", this->_position, this->_radius, this->_height);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
