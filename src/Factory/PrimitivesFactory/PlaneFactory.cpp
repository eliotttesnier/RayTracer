//
// Created by roussierenoa on 5/1/25.
//

#include "PlaneFactory.hpp"
#include "Primitives/Plane/Plane.hpp"

//TODO: Utiliser libloader pour charger les primitives

Raytracer::Factory::PlaneFactory::PlaneFactory(const Math::Point3D &position, const Math::Vector3D &rotation
):
    _position(position),
    _rotation(rotation)
{

}

std::unique_ptr<IPrimitive> Raytracer::Factory::PlaneFactory::create() const {
    return std::make_unique<Raytracer::primitive::Plane>(this->_position, this->_rotation);
}
