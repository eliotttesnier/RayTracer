/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** ALight
*/

#include "ALight.hpp"
#include <limits>
#include <string>
#include <vector>

void ALight::setPosition(float x, float y, float z) {
    _x = x; _y = y; _z = z;
}

void ALight::setColor(float r, float g, float b) {
    _r = r; _g = g; _b = b;
}

void ALight::setIntensity(float intensity) {
    _intensity = intensity;
}

void ALight::getPosition(float &x, float &y, float &z) const {
    x = _x; y = _y; z = _z;
}

void ALight::getColor(float &r, float &g, float &b) const {
    r = _r; g = _g; b = _b;
}

void ALight::getIntensity(float &intensity) const {
    intensity = _intensity;
}

Math::Vector3D ALight::getDirection() const {
    return {};
}

std::string ALight::getLightName() const {
    return this->_lightName;
}

void ALight::setDirection(const Math::Vector3D &direction) {
    (void)direction;
}

bool ALight::isInShadow(
    const Math::Point3D& hitPoint,
    const Math::Vector3D& lightDir,
    const std::vector<std::shared_ptr<IPrimitive>>& primitives
) const {
    const float SHADOW_BIAS = 0.001f;
    Math::Point3D shadowOrigin(
        hitPoint._x + lightDir._x * SHADOW_BIAS,
        hitPoint._y + lightDir._y * SHADOW_BIAS,
        hitPoint._z + lightDir._z * SHADOW_BIAS
    );

    Math::Ray shadowRay(shadowOrigin, lightDir);

    for (const auto& primitive : primitives) {
        Math::hitdata_t shadowHit = primitive->intersect(shadowRay);
        if (shadowHit.hit && shadowHit.distance > 0) {
            return true;
        }
    }
    return false;
}
