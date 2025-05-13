/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteCone
*/

#include <cmath>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
#include "InfiniteCone.hpp"

namespace RayTracer::primitive {

InfiniteCone::InfiniteCone()
{
    _name = "infinite_cone";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _angle = 45.0;
}

InfiniteCone::InfiniteCone(const Math::Point3D &position, double angle)
{
    _name = "infinite_cone";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _angle = angle;
}

Math::hitdata_t InfiniteCone::calculateInfiniteConeIntersection(
    const Math::Ray &localRay) const
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    double theta = _angle * M_PI / 180.0;
    double tan_theta = tan(theta);
    double tan2 = tan_theta * tan_theta;

    double a = localRay.direction._x * localRay.direction._x +
               localRay.direction._z * localRay.direction._z -
               tan2 * localRay.direction._y * localRay.direction._y;

    double b = 2.0 * (localRay.origin._x * localRay.direction._x +
                      localRay.origin._z * localRay.direction._z -
                      tan2 * localRay.origin._y * localRay.direction._y);

    double c = localRay.origin._x * localRay.origin._x +
               localRay.origin._z * localRay.origin._z -
               tan2 * localRay.origin._y * localRay.origin._y;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitData;

    double sqrtd = sqrt(discriminant);
    double t1 = (-b - sqrtd) / (2.0 * a);
    double t2 = (-b + sqrtd) / (2.0 * a);

    if (t1 > t2)
        std::swap(t1, t2);

    double t = t1;
    if (t < 0.001)
        t = t2;
    if (t < 0.001)
        return hitData;

    Math::Point3D localHitPoint(
        localRay.origin._x + t * localRay.direction._x,
        localRay.origin._y + t * localRay.direction._y,
        localRay.origin._z + t * localRay.direction._z
    );

    if (localHitPoint._y < 0)
        return hitData;

    hitData.hit = true;
    hitData.distance = t;
    hitData.point = transformPointToWorld(localHitPoint);

    Math::Vector3D localNormal(
        localHitPoint._x,
        -tan2 * localHitPoint._y,
        localHitPoint._z
    );
    localNormal.normalize();

    hitData.normal = transformNormalToWorld(localNormal);
    hitData.color = _color;

    return hitData;
}

Math::hitdata_t InfiniteCone::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);
    return calculateInfiniteConeIntersection(localRay);
}

Graphic::color_t InfiniteCone::getColor(
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

}  // namespace RayTracer::primitive
