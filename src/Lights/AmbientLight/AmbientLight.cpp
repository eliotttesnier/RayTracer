//
// Created by roussierenoa on 4/28/25.
//

#include "AmbientLight.hpp"
#include <iostream>

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

Graphic::color_t RayTracer::light::AmbientLight::calculateLighting(
    const Math::hitdata_t& hitData,
    const Math::Ray& ray,
    const Math::Vector3D& viewDir
) const
{
    Graphic::color_t baseColor = hitData.color;
    Graphic::color_t ambientColor = {0, 0, 0, baseColor.a};

    ambientColor.r = baseColor.r * _intensity * _r;
    ambientColor.g = baseColor.g * _intensity * _g;
    ambientColor.b = baseColor.b * _intensity * _b;
    return ambientColor;
}
