//
// Created by roussierenoa on 4/28/25.
//

#include "DirectionalLight.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

namespace RayTracer::light {

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

lightInfos_t DirectionalLight::intersect(
    const Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives
) const
{
    Math::Vector3D lightDir = -_direction.normalized();
    lightInfos_t infos;
    infos.hit = !isInShadow(hitPoint, lightDir, primitives);
    infos.lightDir = lightDir;
    return infos;
}

}  // namespace RayTracer::light
