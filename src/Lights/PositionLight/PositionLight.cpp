//
// Created by roussierenoa on 4/28/25.
//

#include "PositionLight.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

namespace RayTracer::light {

    PositionLight::PositionLight(const Math::Vector3D &direction)
        : _direction(direction)
    {
        this->_lightName = "PositionLight";
    }

    void PositionLight::setDirection(const Math::Vector3D &direction)
    {
        this->_direction = direction;
    }

    Math::Vector3D PositionLight::getDirection() const
    {
        return this->_direction;
    }

    bool PositionLight::intersect(
        const Math::Ray &ray,
        const Math::Point3D &hitPoint,
        std::vector<std::shared_ptr<IPrimitive>> primitives
    ) const
    {
        Math::Vector3D lightDir = -this->_direction.normalized();
        return !isInShadow(hitPoint, lightDir, primitives);
    }

}  // namespace RayTracer::light
