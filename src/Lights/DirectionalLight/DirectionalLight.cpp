//
// Created by roussierenoa on 4/28/25.
//

#include "DirectionalLight.hpp"
#include <iostream>

using namespace RayTracer::light;

DirectionalLight::DirectionalLight(const Math::Vector3D &direction)
    : _direction(direction)
{
    this->_lightName = "DirectionalLight";
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
    Math::Vector3D lightDir = _direction.normalized();
    Math::Ray shadowRay(hitPoint, -lightDir);

    for (const auto &primitive : primitives) {
        Math::hitdata_t hitData = primitive->intersect(shadowRay);
        if (hitData.hit && hitData.distance > 1e-4) {
            return false;
        }
    }
    return true;
}
