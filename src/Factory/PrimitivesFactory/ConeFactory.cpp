//
// Created by roussierenoa on 5/1/25.
//

#include "ConeFactory.hpp"
#include "Primitives/Cone/Cone.hpp"

//TODO: Utiliser Libloader pour charger les primitives

RayTracer::Factory::ConeFactory::ConeFactory(const Math::Point3D &position, double radius, double height):
    _position(position),
    _radius(radius),
    _height(height)
{

}

std::unique_ptr<IPrimitive> RayTracer::Factory::ConeFactory::create() const {
    return std::make_unique<RayTracer::primitive::Cone>(this->_position, this->_radius, this->_height);
}
