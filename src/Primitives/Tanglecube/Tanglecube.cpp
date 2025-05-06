/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Tanglecube
*/

#include <cmath>
#include <string>
#include <algorithm>
#include <limits>
#include <iostream>
#include "Tanglecube.hpp"

namespace RayTracer::primitive {

Tanglecube::Tanglecube()
{
    _name = "tanglecube";
    _type = "tanglecube";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _size = 1.0;
}

Tanglecube::Tanglecube(const Math::Point3D &position, double size)
{
    _name = "tanglecube";
    _type = "tanglecube";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _size = size;
}

std::string &Tanglecube::getName()
{
    return _name;
}

std::string &Tanglecube::getType()
{
    return _type;
}

Math::Point3D &Tanglecube::getPosition()
{
    return _position;
}

Math::Vector3D &Tanglecube::getRotation()
{
    return _rotation;
}

double Tanglecube::getSize() const
{
    return _size;
}

void Tanglecube::setSize(double size)
{
    _size = size;
}

Math::Vector3D Tanglecube::normalAt(const Math::Point3D& point) const
{
    const double epsilon = 0.0001;
    double dx = signedDistanceFunction(Math::Point3D(point._x + epsilon, point._y, point._z)) -
               signedDistanceFunction(Math::Point3D(point._x - epsilon, point._y, point._z));
    double dy = signedDistanceFunction(Math::Point3D(point._x, point._y + epsilon, point._z)) -
               signedDistanceFunction(Math::Point3D(point._x, point._y - epsilon, point._z));
    double dz = signedDistanceFunction(Math::Point3D(point._x, point._y, point._z + epsilon)) -
               signedDistanceFunction(Math::Point3D(point._x, point._y, point._z - epsilon));

    Math::Vector3D normal(dx, dy, dz);
    normal.normalize();
    return normal;
}

double Tanglecube::signedDistanceFunction(const Math::Point3D& point) const
{
    double x = point._x - _position._x;
    double y = point._y - _position._y;
    double z = point._z - _position._z;

    x /= (_size * 0.25);
    y /= (_size * 0.25);
    z /= (_size * 0.25);

    double x2 = x * x;
    double y2 = y * y;
    double z2 = z * z;

    double x4 = x2 * x2;
    double y4 = y2 * y2;
    double z4 = z2 * z2;

    return x4 - 5.0 * x2 + y4 - 5.0 * y2 + z4 - 5.0 * z2 + 11.8;
}

Math::hitdata_t Tanglecube::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = {0, 255, 255, 1.0};  // Cyan

    const int MAX_ITERATIONS = 100;
    const double EPSILON = 0.001;
    const double MAX_DIST = 20.0;

    double boundingRadius = _size * 4.0;

    Math::Point3D center = _position;
    Math::Vector3D oc(
        ray.origin._x - center._x,
        ray.origin._y - center._y,
        ray.origin._z - center._z
    );

    double a = ray.direction._x * ray.direction._x +
               ray.direction._y * ray.direction._y +
               ray.direction._z * ray.direction._z;

    double b = 2.0 * (oc._x * ray.direction._x +
                      oc._y * ray.direction._y +
                      oc._z * ray.direction._z);

    double c = oc._x * oc._x + oc._y * oc._y + oc._z * oc._z - boundingRadius * boundingRadius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

        if (t0 > t1) std::swap(t0, t1);

        double tStart = std::max(0.01, t0);
        double tEnd = std::min(MAX_DIST, t1);

        if (tEnd <= 0)
            return hitData;

        double tStep = (tEnd - tStart) / MAX_ITERATIONS;
        double prevValue = signedDistanceFunction(Math::Point3D(
            ray.origin._x + tStart * ray.direction._x,
            ray.origin._y + tStart * ray.direction._y,
            ray.origin._z + tStart * ray.direction._z
        ));

        for (int i = 1; i <= MAX_ITERATIONS && tStart < tEnd; i++) {
            double t = tStart + i * tStep;

            Math::Point3D point(
                ray.origin._x + t * ray.direction._x,
                ray.origin._y + t * ray.direction._y,
                ray.origin._z + t * ray.direction._z
            );

            double currentValue = signedDistanceFunction(point);

            if (currentValue * prevValue <= 0 || std::abs(currentValue) < EPSILON) {
                double tLeft = t - tStep;
                double tRight = t;

                for (int j = 0; j < 10; j++) {
                    double tMid = (tLeft + tRight) * 0.5;

                    Math::Point3D midPoint(
                        ray.origin._x + tMid * ray.direction._x,
                        ray.origin._y + tMid * ray.direction._y,
                        ray.origin._z + tMid * ray.direction._z
                    );

                    double midValue = signedDistanceFunction(midPoint);

                    if (std::abs(midValue) < EPSILON) {
                        hitData.hit = true;
                        hitData.distance = tMid;
                        hitData.point = midPoint;
                        hitData.normal = normalAt(midPoint);
                        return hitData;
                    }

                    if (midValue * currentValue <= 0) {
                        tLeft = tMid;
                    } else {
                        tRight = tMid;
                    }
                }

                double tFinal = (tLeft + tRight) * 0.5;
                Math::Point3D finalPoint(
                    ray.origin._x + tFinal * ray.direction._x,
                    ray.origin._y + tFinal * ray.direction._y,
                    ray.origin._z + tFinal * ray.direction._z
                );

                hitData.hit = true;
                hitData.distance = tFinal;
                hitData.point = finalPoint;
                hitData.normal = normalAt(finalPoint);
                return hitData;
            }

            prevValue = currentValue;
        }
    }

    return hitData;
}

} // namespace Raytracer::primitive