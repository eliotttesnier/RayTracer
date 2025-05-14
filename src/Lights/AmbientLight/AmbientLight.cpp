//
// Created by roussierenoa on 4/28/25.
//

#include "AmbientLight.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

RayTracer::light::AmbientLight::AmbientLight()
{
    this->_lightName = "AmbientLight";
}

bool RayTracer::light::AmbientLight::intersect(
    const Math::Ray &ray,
    const Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives
) const
{
    (void)ray;
    (void)hitPoint;
    (void)primitives;
    return true;
}
