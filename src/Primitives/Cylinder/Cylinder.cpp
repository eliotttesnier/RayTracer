/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** Cylinder
*/

#include <cmath>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include "Cylinder.hpp"
namespace RayTracer::primitive {

Cylinder::Cylinder()
{
    _name = "cylinder";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _height = 1.0;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_height/2.0, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _height/2.0, _radius);
}

Cylinder::Cylinder(const Math::Point3D &position, double radius, double height)
{
    _name = "cylinder";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _height = height;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_height/2.0, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _height/2.0, _radius);
}

double Cylinder::getRadius() const
{
    return _radius;
}

void Cylinder::setRadius(double radius)
{
    _radius = radius;
    _boundingBox.min._x = -_radius;
    _boundingBox.min._z = -_radius;
    _boundingBox.max._x = _radius;
    _boundingBox.max._z = _radius;
}

double Cylinder::getHeight() const
{
    return _height;
}

void Cylinder::setHeight(double height)
{
    _height = height;
    _anchorPoint = Math::Vector3D(0, _height / 2.0, 0);
    _boundingBox.min._y = -_height/2.0;
    _boundingBox.max._y = _height/2.0;
}

Math::Vector3D Cylinder::normalAt(const Math::Point3D& point) const
{
    Math::Point3D localPoint = transformPointToLocal(point);
    Math::Vector3D localNormal;

    if (std::abs(localPoint._y - _anchorPoint._y) < 0.001) {
        localNormal = Math::Vector3D(0, 1, 0);
    } else if (std::abs(localPoint._y + _anchorPoint._y) < 0.001) {
        localNormal = Math::Vector3D(0, -1, 0);
    } else {
        localNormal = Math::Vector3D(localPoint._x, 0, localPoint._z);
        localNormal.normalize();
    }

    return transformNormalToWorld(localNormal);
}

Math::hitdata_t Cylinder::calculateCylinderIntersection(const Math::Ray &localRay) const
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    Math::Vector3D oc(localRay.origin._x, 0, localRay.origin._z);
    Math::Vector3D dir(localRay.direction._x, 0, localRay.direction._z);

    double a = dir.dot(dir);
    double b = 2.0 * oc.dot(dir);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;
    double cylinder_t = std::numeric_limits<double>::infinity();

    if (discriminant >= 0) {
        double sqrtd = sqrt(discriminant);
        double t1 = (-b - sqrtd) / (2.0 * a);
        double t2 = (-b + sqrtd) / (2.0 * a);

        double y1 = localRay.origin._y + t1 * localRay.direction._y;
        double y2 = localRay.origin._y + t2 * localRay.direction._y;

        if (y1 >= -_anchorPoint._y && y1 <= _anchorPoint._y && t1 > 0.001) {
            cylinder_t = t1;
        } else if (y2 >= -_anchorPoint._y && y2 <= _anchorPoint._y && t2 > 0.001) {
            cylinder_t = t2;
        }
    }

    double top_t = std::numeric_limits<double>::infinity();
    if (std::abs(localRay.direction._y) > 0.001) {
        double t = (_anchorPoint._y - localRay.origin._y) / localRay.direction._y;

        if (t > 0.001) {
            double x = localRay.origin._x + t * localRay.direction._x;
            double z = localRay.origin._z + t * localRay.direction._z;

            if (x * x + z * z <= _radius * _radius) {
                top_t = t;
            }
        }
    }

    double bottom_t = std::numeric_limits<double>::infinity();
    if (std::abs(localRay.direction._y) > 0.001) {
        double t = (-_anchorPoint._y - localRay.origin._y) / localRay.direction._y;

        if (t > 0.001) {
            double x = localRay.origin._x + t * localRay.direction._x;
            double z = localRay.origin._z + t * localRay.direction._z;

            if (x * x + z * z <= _radius * _radius) {
                bottom_t = t;
            }
        }
    }

    double t = std::min({cylinder_t, top_t, bottom_t});

    if (std::isfinite(t)) {
        hitData.hit = true;
        hitData.distance = t;

        Math::Point3D localHitPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        Math::Vector3D localNormal;
        if (t == top_t) {
            localNormal = Math::Vector3D(0, 1, 0);
        } else if (t == bottom_t) {
            localNormal = Math::Vector3D(0, -1, 0);
        } else {
            localNormal = Math::Vector3D(localHitPoint._x, 0, localHitPoint._z);
            localNormal.normalize();
        }

        hitData.point = transformPointToWorld(localHitPoint);
        hitData.normal = transformNormalToWorld(localNormal);
    }

    hitData.color = _color;
    return hitData;
}

Math::hitdata_t Cylinder::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);
    Math::hitdata_t hitData;
    hitData.hit = false;

    if (!_boundingBox.intersect(localRay))
        return hitData;

    return calculateCylinderIntersection(localRay);
}

Graphic::color_t Cylinder::getColor(
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

}
