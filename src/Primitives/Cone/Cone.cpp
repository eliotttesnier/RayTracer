/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#include <cmath>
#include <string>
#include <iostream>

#include "Cone.hpp"

namespace RayTracer::primitive {

Cone::Cone()
{
    _name = "cone";
    _type = "cone";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _height = 1.0;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
}

Cone::Cone(const Math::Point3D &position, double radius, double height)
{
    _name = "cone";
    _type = "cone";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _height = height;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
}

double Cone::getRadius() const
{
    return _radius;
}

void Cone::setRadius(double radius)
{
    _radius = radius;
}

double Cone::getHeight() const
{
    return _height;
}

void Cone::setHeight(double height)
{
    _height = height;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
}

Math::Ray Cone::transformRayToLocal(const Math::Ray &ray) const
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

Math::Point3D Cone::transformPointToLocal(const Math::Point3D &point) const
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

Math::Point3D Cone::transformPointToWorld(const Math::Point3D &localPoint) const
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

Math::Vector3D Cone::transformNormalToWorld(const Math::Vector3D &localNormal) const
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

Math::hitdata_t Cone::calculateConeIntersection(const Math::Ray &localRay) const
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    double k = _radius / _height;
    k = k * k;

    Math::Vector3D oc(
        localRay.origin._x,
        localRay.origin._y + _anchorPoint._y,
        localRay.origin._z
    );

    double a = localRay.direction._x * localRay.direction._x -
               k * localRay.direction._y * localRay.direction._y +
               localRay.direction._z * localRay.direction._z;

    double b = 2.0 * (oc._x * localRay.direction._x -
                      k * oc._y * localRay.direction._y +
                      oc._z * localRay.direction._z);

    double c = oc._x * oc._x -
               k * oc._y * oc._y +
               oc._z * oc._z;

    double discriminant = b * b - 4 * a * c;
    double cone_t = std::numeric_limits<double>::infinity();

    if (discriminant >= 0) {
        double sqrtd = sqrt(discriminant);
        double t1 = (-b - sqrtd) / (2.0 * a);
        double t2 = (-b + sqrtd) / (2.0 * a);

        double y1 = localRay.origin._y + t1 * localRay.direction._y;
        double y2 = localRay.origin._y + t2 * localRay.direction._y;

        if (y1 >= -_anchorPoint._y && y1 <= _anchorPoint._y && t1 > 0.001) {
            cone_t = t1;
        } else if (y2 >= -_anchorPoint._y && y2 <= _anchorPoint._y && t2 > 0.001) {
            cone_t = t2;
        }
    }

    double base_t = std::numeric_limits<double>::infinity();
    if (std::abs(localRay.direction._y) > 0.001) {
        double t = (_anchorPoint._y - localRay.origin._y) / localRay.direction._y;

        if (t > 0.001) {
            double x = localRay.origin._x + t * localRay.direction._x;
            double z = localRay.origin._z + t * localRay.direction._z;
            if (x * x + z * z <= _radius * _radius) {
                base_t = t;
            }
        }
    }

    double t = std::min(cone_t, base_t);
    if (std::isfinite(t)) {
        hitData.hit = true;
        hitData.distance = t;

        Math::Point3D localHitPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        Math::Vector3D localNormal;
        if (t == base_t) {
            localNormal = Math::Vector3D(0, 1, 0);
        } else {
            double apex_y = -_anchorPoint._y;
            double k = _radius / _height;
            double dx = localHitPoint._x;
            double dy = localHitPoint._y - apex_y;
            double dz = localHitPoint._z;

            localNormal = Math::Vector3D(
                2 * dx,
                -2 * (k * k) * dy,
                2 * dz
            );
            localNormal.normalize();
        }

        hitData.point = transformPointToWorld(localHitPoint);
        hitData.normal = transformNormalToWorld(localNormal);
    }

    hitData.color = {0.0, 255.0, 0.0, 1.0};
    return hitData;
}

Math::Vector3D Cone::normalAt(const Math::Point3D& point) const
{
    Math::Point3D localPoint = transformPointToLocal(point);
    Math::Vector3D localNormal;

    if (std::abs(localPoint._y - _anchorPoint._y) < 0.001) {
        localNormal = Math::Vector3D(0, 1, 0);
    } else {
        double k = _radius / _height;
        k = k * k;

        double apex_y = -_anchorPoint._y;
        double dx = localPoint._x;
        double dy = localPoint._y - apex_y;
        double dz = localPoint._z;

        localNormal = Math::Vector3D(
            2 * dx,
            -2 * k * dy,
            2 * dz
        );
        localNormal.normalize();
    }

    return transformNormalToWorld(localNormal);
}

Math::hitdata_t Cone::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);

    return calculateConeIntersection(localRay);
}

void Cone::rotatePointToLocal(Math::Point3D &point, double cosX, double sinX,
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

void Cone::rotateVectorToLocal(Math::Vector3D &vector, double cosX, double sinX,
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

void Cone::rotatePointToWorld(Math::Point3D &point, double cosX, double sinX,
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

void Cone::rotateVectorToWorld(Math::Vector3D &vector, double cosX, double sinX,
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

}  // namespace RayTracer::primitive
