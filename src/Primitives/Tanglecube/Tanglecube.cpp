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
#include <utility>
#include <vector>
#include "Tanglecube.hpp"

namespace RayTracer::primitive {

Tanglecube::Tanglecube()
{
    _name = "tanglecube";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _size = 1.0;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    double boundSize = _size * 2.5;
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-boundSize, -boundSize, -boundSize);
    _boundingBox.max = Math::Point3D(boundSize, boundSize, boundSize);
}

Tanglecube::Tanglecube(const Math::Point3D &position, double size)
{
    _name = "tanglecube";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _size = size;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    double boundSize = _size * 2.5;
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-boundSize, -boundSize, -boundSize);
    _boundingBox.max = Math::Point3D(boundSize, boundSize, boundSize);
}

double Tanglecube::getSize() const
{
    return _size;
}

void Tanglecube::setSize(double size)
{
    _size = size;
    double boundSize = _size * 2.5;
    _boundingBox.min = Math::Point3D(-boundSize, -boundSize, -boundSize);
    _boundingBox.max = Math::Point3D(boundSize, boundSize, boundSize);
}

Math::Vector3D Tanglecube::normalAt(const Math::Point3D& point) const
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

double Tanglecube::SDF(const Math::Point3D& point) const
{
    double x = point._x;
    double y = point._y;
    double z = point._z;

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
    Math::Ray localRay = transformRayToLocal(ray);
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = _color;

    if (!_boundingBox.intersect(localRay))
        return hitData;

    const int MAX_ITERATIONS = 100;
    const double EPSILON = 0.001;
    const double MAX_DIST = 20.0;
    double boundingRadius = _size * 4.0;

    Math::Vector3D oc(localRay.origin._x, localRay.origin._y, localRay.origin._z);
    double a = localRay.direction.dot(localRay.direction);
    double b = 2.0 * oc.dot(localRay.direction);
    double c = oc.dot(oc) - boundingRadius * boundingRadius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

        if (t0 > t1)
            std::swap(t0, t1);

        double tStart = std::max(0.01, t0);
        double tEnd = std::min(MAX_DIST, t1);

        if (tEnd <= 0)
            return hitData;

        double tStep = (tEnd - tStart) / MAX_ITERATIONS;
        double prevValue = SDF(Math::Point3D(
            localRay.origin._x + tStart * localRay.direction._x,
            localRay.origin._y + tStart * localRay.direction._y,
            localRay.origin._z + tStart * localRay.direction._z
        ));

        for (int i = 1; i <= MAX_ITERATIONS && tStart < tEnd; i++) {
            double t = tStart + i * tStep;

            Math::Point3D localPoint(
                localRay.origin._x + t * localRay.direction._x,
                localRay.origin._y + t * localRay.direction._y,
                localRay.origin._z + t * localRay.direction._z
            );

            double currentValue = SDF(localPoint);

            if (currentValue * prevValue <= 0 || std::abs(currentValue) < EPSILON) {
                double tLeft = t - tStep;
                double tRight = t;

                for (int j = 0; j < 10; j++) {
                    double tMid = (tLeft + tRight) * 0.5;

                    Math::Point3D localMidPoint(
                        localRay.origin._x + tMid * localRay.direction._x,
                        localRay.origin._y + tMid * localRay.direction._y,
                        localRay.origin._z + tMid * localRay.direction._z
                    );

                    double midValue = SDF(localMidPoint);

                    if (std::abs(midValue) < EPSILON) {
                        hitData.hit = true;
                        hitData.distance = tMid;
                        hitData.point = transformPointToWorld(localMidPoint);
                        hitData.normal = normalAt(hitData.point);
                        return hitData;
                    }

                    if (midValue * currentValue <= 0) {
                        tLeft = tMid;
                    } else {
                        tRight = tMid;
                    }
                }

                double tFinal = (tLeft + tRight) * 0.5;
                Math::Point3D localFinalPoint(
                    localRay.origin._x + tFinal * localRay.direction._x,
                    localRay.origin._y + tFinal * localRay.direction._y,
                    localRay.origin._z + tFinal * localRay.direction._z
                );

                hitData.hit = true;
                hitData.distance = tFinal;
                hitData.point = transformPointToWorld(localFinalPoint);
                hitData.normal = normalAt(hitData.point);
                return hitData;
            }

            prevValue = currentValue;
        }
    }

    return hitData;
}

Graphic::color_t Tanglecube::getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _material->calculateColor(
        *this,
        hitData,
        ray,
        lights,
        primitives
    );
}

}  // namespace Raytracer::primitive
