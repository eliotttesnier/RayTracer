#include "ALight.hpp"
#include <limits>

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
    // Default implementation does nothing
    (void)direction;
}

bool ALight::isInShadow(
    const Math::Point3D& hitPoint,
    const Math::Vector3D& lightDir,
    const std::vector<std::shared_ptr<IPrimitive>>& primitives
) const {
    // Create a shadow ray from hit point towards light
    const float SHADOW_BIAS = 0.001f; // Prevent self-shadowing due to floating point precision
    Math::Point3D shadowOrigin(
        hitPoint._x + lightDir._x * SHADOW_BIAS,
        hitPoint._y + lightDir._y * SHADOW_BIAS,
        hitPoint._z + lightDir._z * SHADOW_BIAS
    );
    
    Math::Ray shadowRay(shadowOrigin, lightDir);
    
    // Check if any object blocks the light
    for (const auto& primitive : primitives) {
        Math::hitdata_t shadowHit = primitive->intersect(shadowRay);
        if (shadowHit.hit && shadowHit.distance > 0) {
            return true; // In shadow
        }
    }
    
    return false; // Not in shadow
}
