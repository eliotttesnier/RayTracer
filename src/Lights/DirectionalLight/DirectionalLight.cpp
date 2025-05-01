//
// Created by roussierenoa on 4/28/25.
//

#include "DirectionalLight.hpp"
#include <iostream>

using namespace Raytracer::light;

DirectionalLight::DirectionalLight(const Math::Vector3D &direction)
    : _direction(direction)
{
}

void DirectionalLight::setDirection(const Math::Vector3D &direction)
{
    _direction = direction;
}

Math::Vector3D DirectionalLight::getDirection() const
{
    return _direction;
}

bool DirectionalLight::intersect(
    const Math::Ray &ray,
    Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives
) const
{
    (void)ray;
    (void)hitPoint;
    (void)primitives;
    return true;
}
