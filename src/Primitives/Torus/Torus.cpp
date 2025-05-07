/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Torus
*/

#include <cmath>
#include <string>
#include <algorithm>
#include <limits>
#include "Torus.hpp"

namespace RayTracer::primitive {

Torus::Torus()
{
    _name = "torus";
    _type = "torus";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _majorRadius = 1.0;
    _minorRadius = 0.25;
    _anchorPoint = Math::Vector3D(0, 0, 0);
}

Torus::Torus(const Math::Point3D &position, double majorRadius, double minorRadius)
{
    _name = "torus";
    _type = "torus";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _majorRadius = majorRadius;
    _minorRadius = minorRadius;
    _anchorPoint = Math::Vector3D(0, 0, 0);
}

double Torus::getMajorRadius() const
{
    return _majorRadius;
}

void Torus::setMajorRadius(double radius)
{
    _majorRadius = radius;
}

double Torus::getMinorRadius() const
{
    return _minorRadius;
}

void Torus::setMinorRadius(double radius)
{
    _minorRadius = radius;
}

Math::Vector3D Torus::normalAt(const Math::Point3D& point) const
{
    Math::Point3D localPoint = transformPointToLocal(point);
    const double epsilon = 0.0001;
    double dx = SDF(Math::Point3D(localPoint._x + epsilon, localPoint._y, localPoint._z)) -
                SDF(Math::Point3D(localPoint._x - epsilon, localPoint._y, localPoint._z));
    double dy = SDF(Math::Point3D(localPoint._x, localPoint._y + epsilon, localPoint._z)) -
                SDF(Math::Point3D(localPoint._x, localPoint._y - epsilon, localPoint._z));
    double dz = SDF(Math::Point3D(localPoint._x, localPoint._y, localPoint._z + epsilon)) -
                SDF(Math::Point3D(localPoint._x, localPoint._y, localPoint._z - epsilon));

    Math::Vector3D localNormal(dx, dy, dz);
    localNormal.normalize();

    return transformNormalToWorld(localNormal);
}

double Torus::SDF(const Math::Point3D& point) const {
    Math::Point3D localPoint = transformPointToLocal(point);

    double lengthXZ = sqrt(localPoint._x * localPoint._x + localPoint._z * localPoint._z);
    double dist =
        sqrt(pow(lengthXZ - _majorRadius, 2) + localPoint._y * localPoint._y) - _minorRadius;
    return dist;
}

Math::hitdata_t Torus::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);

    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = {255.0, 255.0, 0.0, 1.0};  // Yellow

    const int MAX_STEPS = 128;
    const double EPSILON = 0.0001;
    const double MAX_DIST = 100.0;
    double boundingRadius = _majorRadius + _minorRadius;
    Math::Vector3D oc(localRay.origin._x, localRay.origin._y, localRay.origin._z);
    double a = localRay.direction.dot(localRay.direction);
    double b = 2.0 * oc.dot(localRay.direction);
    double c = oc.dot(oc) - boundingRadius * boundingRadius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitData;

    double t = 0.01;
    for (int i = 0; i < MAX_STEPS && t < MAX_DIST; i++) {
        Math::Point3D localPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        double lengthXZ = sqrt(localPoint._x * localPoint._x + localPoint._z * localPoint._z);
        double dist = sqrt(pow(lengthXZ - _majorRadius, 2) +
            localPoint._y * localPoint._y) - _minorRadius;

        if (dist < EPSILON) {
            hitData.hit = true;
            hitData.distance = t;
            hitData.point = transformPointToWorld(localPoint);
            hitData.normal = normalAt(hitData.point);
            break;
        }
        t += dist;
    }

    return hitData;
}

}  // namespace Raytracer::primitive
