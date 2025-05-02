//
// Created by roussierenoa on 5/1/25.
//

#include "SphereFactory.hpp"
#include "Primitives/Sphere/Sphere.hpp"

//TODO: Utiliser Libloader pour charger les primitives

Raytracer::Factory::SphereFactory::SphereFactory(const Math::Point3D &position, double radius
):
    _position(position),
    _radius(radius)
{

}

std::unique_ptr<IPrimitive> Raytracer::Factory::SphereFactory::create() const {
    return std::make_unique<Raytracer::primitive::Sphere>(_position, _radius);
}
