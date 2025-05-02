//
// Created by roussierenoa on 5/1/25.
//

#include "SphereFactory.hpp"
#include "Primitives/Sphere/Sphere.hpp"

//TODO: Utiliser Libloader pour charger les primitives

RayTracer::Factory::SphereFactory::SphereFactory(const Math::Point3D &position, double radius
):
    _position(position),
    _radius(radius)
{

}

std::unique_ptr<IPrimitive> RayTracer::Factory::SphereFactory::create() const {
    return std::make_unique<RayTracer::primitive::Sphere>(_position, _radius);
}
