#include "ALight.hpp"

void ALight::setPosition(float x, float y, float z) {
    _x = x; _y = y; _z = z;
}

void ALight::setColor(float r, float g, float b) {
    _r = r; _g = g; _b = b;
}

void ALight::setIntensity(float intensity) {
    _intensity = intensity;
}

void ALight::setDirection(const Math::Vector3D &direction) {
    return;
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
