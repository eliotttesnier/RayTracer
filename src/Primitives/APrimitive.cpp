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
#include <memory>

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

const Math::Vector3D APrimitive::getShear() const
{
    return _shear;
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

void APrimitive::setShear(const Math::Vector3D &shear)
{
    _shear = shear;
}

void APrimitive::setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material)
{
    _material = material;
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
    (void) hitData;
    (void) ray;
    (void) lights;
    (void) primitives;
    return Graphic::color_t{0.0, 0.0, 0.0, 1.0};
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

    localOrigin._x -= _shear._x * localOrigin._y + _shear._y * localOrigin._z;
    localOrigin._y -= _shear._z * localOrigin._z;

    rotatePointToLocal(localOrigin, cosX, sinX, cosY, sinY, cosZ, sinZ);

    if (_scale._x != 0) localOrigin._x /= _scale._x;
    if (_scale._y != 0) localOrigin._y /= _scale._y;
    if (_scale._z != 0) localOrigin._z /= _scale._z;

    Math::Vector3D localDirection = ray.direction;

    localDirection._x -= _shear._x * localDirection._y + _shear._y * localDirection._z;
    localDirection._y -= _shear._z * localDirection._z;

    rotateVectorToLocal(localDirection, cosX, sinX, cosY, sinY, cosZ, sinZ);

    if (_scale._x != _scale._y || _scale._y != _scale._z || _scale._x != _scale._z) {
        if (_scale._x != 0) localDirection._x /= _scale._x;
        if (_scale._y != 0) localDirection._y /= _scale._y;
        if (_scale._z != 0) localDirection._z /= _scale._z;
        localDirection.normalize();
    }

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

    localPoint._x -= _shear._x * localPoint._y + _shear._y * localPoint._z;
    localPoint._y -= _shear._z * localPoint._z;

    rotatePointToLocal(localPoint, cosX, sinX, cosY, sinY, cosZ, sinZ);

    if (_scale._x != 0) localPoint._x /= _scale._x;
    if (_scale._y != 0) localPoint._y /= _scale._y;
    if (_scale._z != 0) localPoint._z /= _scale._z;

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
    worldPoint._x *= _scale._x;
    worldPoint._y *= _scale._y;
    worldPoint._z *= _scale._z;

    rotatePointToWorld(worldPoint, cosX, sinX, cosY, sinY, cosZ, sinZ);

    worldPoint._x += _shear._x * worldPoint._y + _shear._y * worldPoint._z;
    worldPoint._y += _shear._z * worldPoint._z;

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

    Math::Vector3D scaledNormal = localNormal;
    scaledNormal._x *= (_scale._x != 0) ? (1.0 / _scale._x) : 1.0;
    scaledNormal._y *= (_scale._y != 0) ? (1.0 / _scale._y) : 1.0;
    scaledNormal._z *= (_scale._z != 0) ? (1.0 / _scale._z) : 1.0;

    if (_shear._x != 0 || _shear._y != 0 || _shear._z != 0) {
        scaledNormal._y -= _shear._x * scaledNormal._x;
        scaledNormal._z -= _shear._y * scaledNormal._x + _shear._z * scaledNormal._y;
    }

    Math::Vector3D worldNormal = scaledNormal;
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
