//
// Created by roussierenoa on 4/28/25.
//

#include "PointLight.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

namespace RayTracer::light {

    PointLight::PointLight(const Math::Vector3D &direction)
        : _direction(direction)
    {
        this->_lightName = "PositionLight";
    }

    void PointLight::setDirection(const Math::Vector3D &direction)
    {
        this->_direction = direction;
    }

    Math::Vector3D PointLight::getDirection() const
    {
        return this->_direction;
    }

    bool PointLight::intersect(
        const Math::Ray &ray,
        const Math::Point3D &hitPoint,
        std::vector<std::shared_ptr<IPrimitive>> primitives
    ) const
    {
        Math::Vector3D lightDir = -this->_direction.normalized();
        return !isInShadow(hitPoint, lightDir, primitives);
    }

}  // namespace RayTracer::light
