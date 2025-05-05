//
// Created by roussierenoa on 4/28/25.
//

#include "AmbientLight.hpp"
#include <iostream>

RayTracer::light::AmbientLight::AmbientLight()
{
}

bool RayTracer::light::AmbientLight::intersect(
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

std::string RayTracer::light::AmbientLight::getType()
{
    return "AmbientLight";
}
