/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#include <cmath>
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

#include "Cone.hpp"

namespace RayTracer::primitive {

Cone::Cone()
{
    _name = "cone";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _height = 1.0;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_height/2.0, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _height/2.0, _radius);
}

Cone::Cone(const Math::Point3D &position, double radius, double height)
{
    _name = "cone";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _height = height;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_height/2.0, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _height/2.0, _radius);
}

double Cone::getRadius() const
{
    return _radius;
}

void Cone::setRadius(double radius)
{
    _radius = radius;
    _boundingBox.min._x = -_radius;
    _boundingBox.min._z = -_radius;
    _boundingBox.max._x = _radius;
    _boundingBox.max._z = _radius;
}

double Cone::getHeight() const
{
    return _height;
}

void Cone::setHeight(double height)
{
    _height = height;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
    _boundingBox.min._y = -_height/2.0;
    _boundingBox.max._y = _height/2.0;
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

    hitData.color = _color;
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
    Math::hitdata_t hitData;
    hitData.hit = false;

    if (!_boundingBox.intersect(localRay))
        return hitData;

    return calculateConeIntersection(localRay);
}

Graphic::color_t Cone::getColor(
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
