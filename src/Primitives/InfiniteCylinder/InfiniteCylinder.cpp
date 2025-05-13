/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteCylinder
*/

#include <cmath>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include "InfiniteCylinder.hpp"

namespace RayTracer::primitive {

InfiniteCylinder::InfiniteCylinder()
{
    _name = "infinite_cylinder";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
}

InfiniteCylinder::InfiniteCylinder(const Math::Point3D &position, double radius)
{
    _name = "infinite_cylinder";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
}

Math::hitdata_t InfiniteCylinder::calculateInfiniteCylinderIntersection(
    const Math::Ray &localRay) const
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    Math::Vector3D oc(localRay.origin._x, 0, localRay.origin._z);
    Math::Vector3D dir(localRay.direction._x, 0, localRay.direction._z);

    double a = dir.dot(dir);
    double b = 2.0 * oc.dot(dir);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double sqrtd = sqrt(discriminant);
        double t = (-b - sqrtd) / (2.0 * a);

        if (t > 0.001) {
            hitData.hit = true;
            hitData.distance = t;

            Math::Point3D localHitPoint(
                localRay.origin._x + t * localRay.direction._x,
                localRay.origin._y + t * localRay.direction._y,
                localRay.origin._z + t * localRay.direction._z
            );

            Math::Vector3D localNormal(localHitPoint._x, 0, localHitPoint._z);
            localNormal.normalize();

            hitData.point = transformPointToWorld(localHitPoint);
            hitData.normal = transformNormalToWorld(localNormal);
            hitData.color = _color;
        }
    }

    return hitData;
}

Math::hitdata_t InfiniteCylinder::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);
    return calculateInfiniteCylinderIntersection(localRay);
}

Graphic::color_t InfiniteCylinder::getColor(
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
