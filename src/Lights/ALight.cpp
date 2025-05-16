/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** ALight
*/

#include "ALight.hpp"
#include <limits>
#include <tuple>
#include <string>
#include <vector>

void ALight::setPosition(const Math::Point3D &point) {
    this->_position = point;
}

void ALight::setColor(int r, int g, int b) {
    this->_r = r;
    this->_g = g;
    this->_b = b;
}

void ALight::setIntensity(float intensity) {
    this->_intensity = intensity;
}

Math::Point3D ALight::getPosition() const {
    return this->_position;
}

std::tuple<int, int, int> ALight::getColor() const {
    return {this->_r, this->_g, this->_b};
}

float ALight::getIntensity() const {
    return _intensity;
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
    const std::vector<std::shared_ptr<IPrimitive>> &primitives
) const {
    const float SHADOW_BIAS = 0.001f;
    Math::Point3D shadowOrigin(
        hitPoint._x + lightDir._x * SHADOW_BIAS,
        hitPoint._y + lightDir._y * SHADOW_BIAS,
        hitPoint._z + lightDir._z * SHADOW_BIAS
    );

    Math::Ray shadowRay(shadowOrigin, lightDir);

    for (const auto &primitive : primitives) {
        Math::hitdata_t shadowHit = primitive->intersect(shadowRay);
        if (shadowHit.hit && shadowHit.distance > 0) {
            return true;
        }
    }
    return false;
}
