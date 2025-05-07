/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"
#include <string>
#include <vector>
#include <algorithm>

const std::string APrimitive::getName() const
{
    return _name;
}

const std::string APrimitive::getType() const
{
    return _type;
}

const Math::Point3D APrimitive::getPosition() const
{
    return _position;
}

const Math::Vector3D APrimitive::getRotation() const
{
    return _rotation;
}

void APrimitive::setName(const std::string &name)
{
    _name = name;
}

void APrimitive::setType(const std::string &type)
{
    _type = type;
}

void APrimitive::setPosition(const Math::Point3D &position)
{
    _position = position;
}

void APrimitive::setRotation(const Math::Vector3D &rotation)
{
    _rotation = rotation;
}

void APrimitive::setScale(const Math::Vector3D &scale) {
    _scale = scale;
}

Math::hitdata_t APrimitive::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.distance = 0.0;
    hitData.point = Math::Point3D();
    hitData.normal = Math::Vector3D();
    hitData.color = Graphic::color_t{0.0, 0.0, 0.0, 1.0};
    return hitData;
}

Graphic::color_t APrimitive::getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (lights.empty()) {
        return hitData.color;
    }

    Graphic::color_t baseColor = hitData.color;

    Graphic::color_t finalColor = {
        baseColor.r * 0.05,
        baseColor.g * 0.05,
        baseColor.b * 0.05,
        baseColor.a
    };

    Math::Vector3D viewDir = -ray.direction.normalized();

    for (const auto& light : lights) {
        if (light->intersect(ray, hitData.point, primitives)) {
            Graphic::color_t lightContribution =
                light->calculateLighting(hitData, ray, viewDir);

            finalColor.r += lightContribution.r;
            finalColor.g += lightContribution.g;
            finalColor.b += lightContribution.b;
        }
    }

    finalColor.r = std::pow(finalColor.r / 255.0, 1.0 / 2.2) * 255.0;
    finalColor.g = std::pow(finalColor.g / 255.0, 1.0 / 2.2) * 255.0;
    finalColor.b = std::pow(finalColor.b / 255.0, 1.0 / 2.2) * 255.0;

    finalColor.r = std::max(0.0, std::min(255.0, finalColor.r));
    finalColor.g = std::max(0.0, std::min(255.0, finalColor.g));
    finalColor.b = std::max(0.0, std::min(255.0, finalColor.b));

    return finalColor;
}

Math::Ray APrimitive::transformRayToLocal(const Math::Ray &ray) const
{
    double radX = _rotation._x * M_PI / 180.0;
    double radY = _rotation._y * M_PI / 180.0;
    double radZ = _rotation._z * M_PI / 180.0;
    double cosX = cos(radX);
    double sinX = sin(radX);
    double cosY = cos(radY);
    double sinY = sin(radY);
    double cosZ = cos(radZ);
    double sinZ = sin(radZ);

    Math::Point3D localOrigin(
        ray.origin._x - _position._x,
        ray.origin._y - _position._y + _anchorPoint._y,
        ray.origin._z - _position._z
    );

    rotatePointToLocal(localOrigin, cosX, sinX, cosY, sinY, cosZ, sinZ);

    Math::Vector3D localDirection = ray.direction;
    rotateVectorToLocal(localDirection, cosX, sinX, cosY, sinY, cosZ, sinZ);

    return Math::Ray(localOrigin, localDirection);
}

Math::Point3D APrimitive::transformPointToLocal(const Math::Point3D &point) const
{
    double radX = _rotation._x * M_PI / 180.0;
    double radY = _rotation._y * M_PI / 180.0;
    double radZ = _rotation._z * M_PI / 180.0;
    double cosX = cos(radX);
    double sinX = sin(radX);
    double cosY = cos(radY);
    double sinY = sin(radY);
    double cosZ = cos(radZ);
    double sinZ = sin(radZ);

    Math::Point3D localPoint(
        point._x - _position._x,
        point._y - _position._y + _anchorPoint._y,
        point._z - _position._z
    );

    rotatePointToLocal(localPoint, cosX, sinX, cosY, sinY, cosZ, sinZ);

    return localPoint;
}

Math::Point3D APrimitive::transformPointToWorld(const Math::Point3D &localPoint) const
{
    double radX = _rotation._x * M_PI / 180.0;
    double radY = _rotation._y * M_PI / 180.0;
    double radZ = _rotation._z * M_PI / 180.0;
    double cosX = cos(radX);
    double sinX = sin(radX);
    double cosY = cos(radY);
    double sinY = sin(radY);
    double cosZ = cos(radZ);
    double sinZ = sin(radZ);

    Math::Point3D worldPoint = localPoint;
    rotatePointToWorld(worldPoint, cosX, sinX, cosY, sinY, cosZ, sinZ);

    worldPoint._x += _position._x;
    worldPoint._y += _position._y - _anchorPoint._y;
    worldPoint._z += _position._z;

    return worldPoint;
}

Math::Vector3D APrimitive::transformNormalToWorld(const Math::Vector3D &localNormal) const
{
    double radX = _rotation._x * M_PI / 180.0;
    double radY = _rotation._y * M_PI / 180.0;
    double radZ = _rotation._z * M_PI / 180.0;
    double cosX = cos(radX);
    double sinX = sin(radX);
    double cosY = cos(radY);
    double sinY = sin(radY);
    double cosZ = cos(radZ);
    double sinZ = sin(radZ);

    Math::Vector3D worldNormal = localNormal;
    rotateVectorToWorld(worldNormal, cosX, sinX, cosY, sinY, cosZ, sinZ);

    worldNormal.normalize();
    return worldNormal;
}

void APrimitive::rotatePointToLocal(Math::Point3D &point, double cosX, double sinX,
    double cosY, double sinY, double cosZ, double sinZ) const
{
    double origX = point._x;
    point._x = cosZ * origX + sinZ * point._y;
    point._y = -sinZ * origX + cosZ * point._y;

    origX = point._x;
    point._x = cosY * origX - sinY * point._z;
    point._z = sinY * origX + cosY * point._z;

    double origY = point._y;
    point._y = cosX * origY + sinX * point._z;
    point._z = -sinX * origY + cosX * point._z;
}

void APrimitive::rotateVectorToLocal(Math::Vector3D &vector, double cosX, double sinX,
    double cosY, double sinY, double cosZ, double sinZ) const
{
    double origX = vector._x;
    vector._x = cosZ * origX + sinZ * vector._y;
    vector._y = -sinZ * origX + cosZ * vector._y;

    origX = vector._x;
    vector._x = cosY * origX - sinY * vector._z;
    vector._z = sinY * origX + cosY * vector._z;

    double origY = vector._y;
    vector._y = cosX * origY + sinX * vector._z;
    vector._z = -sinX * origY + cosX * vector._z;
}

void APrimitive::rotatePointToWorld(Math::Point3D &point, double cosX, double sinX,
    double cosY, double sinY, double cosZ, double sinZ) const
{
    double origY = point._y;
    point._y = cosX * origY - sinX * point._z;
    point._z = sinX * origY + cosX * point._z;

    double origX = point._x;
    point._x = cosY * origX + sinY * point._z;
    point._z = -sinY * origX + cosY * point._z;

    origX = point._x;
    point._x = cosZ * origX - sinZ * point._y;
    point._y = sinZ * origX + cosZ * point._y;
}

void APrimitive::rotateVectorToWorld(Math::Vector3D &vector, double cosX, double sinX,
    double cosY, double sinY, double cosZ, double sinZ) const
{
    double origY = vector._y;
    vector._y = cosX * origY - sinX * vector._z;
    vector._z = sinX * origY + cosX * vector._z;

    double origX = vector._x;
    vector._x = cosY * origX + sinY * vector._z;
    vector._z = -sinY * origX + cosY * vector._z;

    origX = vector._x;
    vector._x = cosZ * origX - sinZ * vector._y;
    vector._y = sinZ * origX + cosZ * vector._y;
}
