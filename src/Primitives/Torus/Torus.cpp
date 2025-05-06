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
}

Torus::Torus(const Math::Point3D &position, double majorRadius, double minorRadius)
{
    _name = "torus";
    _type = "torus";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _majorRadius = majorRadius;
    _minorRadius = minorRadius;
}

std::string &Torus::getName()
{
    return _name;
}

std::string &Torus::getType()
{
    return _type;
}

Math::Point3D &Torus::getPosition()
{
    return _position;
}

Math::Vector3D &Torus::getRotation()
{
    return _rotation;
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
    Math::Vector3D op(point._x - _position._x,
                      point._y - _position._y,
                      point._z - _position._z);

    double distInXZPlane = sqrt(op._x * op._x + op._z * op._z);

    if (distInXZPlane < 1e-8) {
        return Math::Vector3D(0, (op._y > 0) ? 1 : -1, 0);
    }

    double scale = _majorRadius / distInXZPlane;
    double closestX = op._x * scale;
    double closestZ = op._z * scale;

    Math::Vector3D normal(op._x - closestX, op._y, op._z - closestZ);
    normal.normalize();

    return normal;
}

double Torus::signedDistanceFunction(const Math::Point3D& point) const {
    Math::Vector3D p(point._x - _position._x,
                    point._y - _position._y,
                    point._z - _position._z);

    double lengthXZ = sqrt(p._x * p._x + p._z * p._z);
    double dist = sqrt(pow(lengthXZ - _majorRadius, 2) + p._y * p._y) - _minorRadius;
    return dist;
}

Math::hitdata_t Torus::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = {255.0, 255.0, 0.0, 1.0}; // Yellow

    const int MAX_STEPS = 128;
    const double EPSILON = 0.0001;
    const double MAX_DIST = 100.0;

    double t = 0.01;
    for (int i = 0; i < MAX_STEPS && t < MAX_DIST; i++) {
        Math::Point3D point(
            ray.origin._x + t * ray.direction._x,
            ray.origin._y + t * ray.direction._y,
            ray.origin._z + t * ray.direction._z
        );

        double dist = signedDistanceFunction(point);
        if (dist < EPSILON) {
            hitData.hit = true;
            hitData.distance = t;
            hitData.point = point;
            hitData.normal = normalAt(point);
            break;
        }
        t += dist;
    }
    
    return hitData;
}

} // namespace Raytracer::primitive