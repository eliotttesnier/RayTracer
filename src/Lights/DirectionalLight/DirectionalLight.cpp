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

bool DirectionalLight::intersect(
    const Math::Ray &ray,
    const Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives
) const
{
    Math::Vector3D lightDir = -_direction.normalized();
    return !isInShadow(hitPoint, lightDir, primitives);
}

Graphic::color_t DirectionalLight::calculateLighting(
    const Math::hitdata_t& hitData,
    const Math::Ray& ray,
    const Math::Vector3D& viewDir
) const
{
    const float diffuseStrength = 0.7f;
    const float specularStrength = 0.3f;
    const int specularShininess = 32;

    Graphic::color_t baseColor = hitData.color;
    Graphic::color_t lightContribution = {0.0, 0.0, 0.0, baseColor.a};

    Math::Vector3D normal = hitData.normal.normalized();
    Math::Vector3D lightDir = -_direction.normalized();

    float diffuseFactor = std::max(0.0f,
        static_cast<float>(normal.dot(lightDir)));
    diffuseFactor = diffuseStrength * diffuseFactor * _intensity;

    Math::Vector3D halfwayDir = (lightDir + viewDir).normalized();
    float specularFactor = std::max(0.0f,
        static_cast<float>(normal.dot(halfwayDir)));
    specularFactor = pow(specularFactor, specularShininess) * specularStrength * _intensity;

    bool isWhiteLight = (_r > 0.9f && _g > 0.9f && _b > 0.9f);

    if (isWhiteLight) {
        lightContribution.r += baseColor.r * diffuseFactor;
        lightContribution.g += baseColor.g * diffuseFactor;
        lightContribution.b += baseColor.b * diffuseFactor;

        float specValue = 255.0f * specularFactor;
        lightContribution.r += specValue;
        lightContribution.g += specValue;
        lightContribution.b += specValue;
    } else {
        float scaledIntensity = _intensity * _intensity * 0.1f;

        float objectColorWeight = 1.0f - scaledIntensity;
        float lightColorWeight = scaledIntensity * 0.2f;

        lightContribution.r += (baseColor.r * objectColorWeight +
                                (_r * 255.0f * lightColorWeight * 0.3f)) *
                                diffuseFactor;
        lightContribution.g += (baseColor.g * objectColorWeight +
                                (_g * 255.0f * lightColorWeight * 0.3f)) *
                                diffuseFactor;
        lightContribution.b += (baseColor.b * objectColorWeight +
                                (_b * 255.0f * lightColorWeight * 0.3f)) *
                                diffuseFactor;

        float specScaling = 0.1f;
        lightContribution.r += _r * 255.0f * specularFactor * specScaling;
        lightContribution.g += _g * 255.0f * specularFactor * specScaling;
        lightContribution.b += _b * 255.0f * specularFactor * specScaling;
    }

    return lightContribution;
}

}  // namespace RayTracer::light
