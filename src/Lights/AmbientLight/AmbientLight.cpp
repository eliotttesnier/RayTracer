//
// Created by roussierenoa on 4/28/25.
//

#include "AmbientLight.hpp"
#include <iostream>
#include <algorithm> // Added for std::min

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

    float ambientFactor = _intensity * 0.3f;
    float lightInfluence = std::min(0.7f, _intensity);
    float objectInfluence = 1.0f - lightInfluence;

    float r = (baseColor.r * objectInfluence + _r * lightInfluence) * ambientFactor;
    float g = (baseColor.g * objectInfluence + _g * lightInfluence) * ambientFactor;
    float b = (baseColor.b * objectInfluence + _b * lightInfluence) * ambientFactor;

    ambientColor.r = static_cast<unsigned char>(r > 255.0f ? 255 : r);
    ambientColor.g = static_cast<unsigned char>(g > 255.0f ? 255 : g);
    ambientColor.b = static_cast<unsigned char>(b > 255.0f ? 255 : b);

    return ambientColor;
}
