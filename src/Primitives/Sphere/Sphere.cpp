//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Sphere.hpp"

namespace RayTracer::primitive {

Sphere::Sphere() {
    _name = "sphere";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_radius, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _radius, _radius);
}

Sphere::Sphere(const Math::Point3D &position, double radius) {
    _name = "sphere";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_radius, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _radius, _radius);
}

double Sphere::getRadius() const {
    return _radius;
}

void Sphere::setRadius(double radius) {
    _radius = radius;
}

Math::Vector3D Sphere::normalAt(const Math::Point3D& point) const {
    Math::Point3D localPoint = transformPointToLocal(point);
    Math::Vector3D localNormal(
        localPoint._x,
        localPoint._y,
        localPoint._z
    );
    localNormal.normalize();

    return transformNormalToWorld(localNormal);
}

Math::hitdata_t Sphere::intersect(const Math::Ray &ray) {
    Math::Ray localRay = transformRayToLocal(ray);
    Math::hitdata_t hitData;
    hitData.hit = false;

    if (!_boundingBox.intersect(localRay))
        return hitData;

    Math::Vector3D oc(localRay.origin._x, localRay.origin._y, localRay.origin._z);

    double a = localRay.direction.dot(localRay.direction);
    double b = 2.0 * oc.dot(localRay.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitData;

    double sqrtd = sqrt(discriminant);
    double t1 = (-b - sqrtd) / (2.0 * a);
    double t2 = (-b + sqrtd) / (2.0 * a);
    double t;

    if (t1 > 0.001) {
        t = t1;
        hitData.hit = true;
    } else if (t2 > 0.001) {
        t = t2;
        hitData.hit = true;
    } else {
        return hitData;
    }

    if (hitData.hit) {
        hitData.distance = t;

        Math::Point3D localHitPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        Math::Vector3D localNormal(localHitPoint._x, localHitPoint._y, localHitPoint._z);
        localNormal.normalize();

        hitData.point = transformPointToWorld(localHitPoint);
        hitData.normal = transformNormalToWorld(localNormal);
    }

    hitData.color = _color;
    return hitData;
}

Graphic::color_t Sphere::getColor(
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
