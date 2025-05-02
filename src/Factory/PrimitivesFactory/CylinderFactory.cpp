//
// Created by roussierenoa on 5/1/25.
//

#include "CylinderFactory.hpp"

#include "Primitives/Cylinder/Cylinder.hpp"

//TODO: Utiliser Libloader pour charger les primitives

Raytracer::Factory::CylinderFactory::CylinderFactory(const Math::Point3D &position, double radius, double height):
    _position(position),
    _radius(radius),
    _height(height)
{

}

std::unique_ptr<IPrimitive> Raytracer::Factory::CylinderFactory::create() const {
    return std::make_unique<Raytracer::primitive::Cylinder>(this->_position, this->_radius, this->_height);
}
