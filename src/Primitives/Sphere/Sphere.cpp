//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <cmath>
#include <string>
#include "Sphere.hpp"

namespace RayTracer::primitive {

Sphere::Sphere() {
    _name = "sphere";
    _type = "sphere";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
}

Sphere::Sphere(const Math::Point3D &position, double radius) {
    _name = "sphere";
    _type = "sphere";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
}

double Sphere::getRadius() const {
    return _radius;
}

void Sphere::setRadius(double radius) {
    _radius = radius;
}

Math::Vector3D Sphere::normalAt(const Math::Point3D& point) const {
    Math::Vector3D normal(
        point._x - _position._x,
        point._y - _position._y,
        point._z - _position._z
    );

    double length = sqrt(normal._x * normal._x +
                        normal._y * normal._y +
                        normal._z * normal._z);
    if (length > 1e-8) {
        normal._x /= length;
        normal._y /= length;
        normal._z /= length;
    }

    return normal;
}

Math::hitdata_t Sphere::intersect(const Math::Ray &ray) {
    Math::hitdata_t hitData;

    Math::Vector3D oc(ray.origin._x - _position._x,
                     ray.origin._y - _position._y,
                     ray.origin._z - _position._z);
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    hitData.hit = false;

    if (discriminant < 0) {
        return hitData;
    }

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
        hitData.point = Math::Point3D(
            ray.origin._x + t * ray.direction._x,
            ray.origin._y + t * ray.direction._y,
            ray.origin._z + t * ray.direction._z
        );
        hitData.normal = normalAt(hitData.point);
    }

    hitData.color = {0.0, 0.0, 255.0, 1.0};  // Blue
    return hitData;
}

}
