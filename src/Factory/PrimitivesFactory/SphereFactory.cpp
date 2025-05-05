//
// Created by roussierenoa on 5/1/25.
//

#include "SphereFactory.hpp"
#include "Primitives/Sphere/Sphere.hpp"

RayTracer::Factory::SphereFactory::SphereFactory(const Math::Point3D &position, double radius
):
    _position(position),
    _radius(radius)
{

}

std::unique_ptr<IPrimitive> RayTracer::Factory::SphereFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("Sphere"))
        throw std::runtime_error("Sphere plugin not found");
    auto obj = plugins["Sphere"]->initEntryPointPtr<primitive::Sphere>("create", this->_position, this->_radius);
    return std::unique_ptr<IPrimitive>(obj);
}
