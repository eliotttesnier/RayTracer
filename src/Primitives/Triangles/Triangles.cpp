/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** Triangles
*/

#include <cmath>
#include "Triangles.hpp"

namespace RayTracer::primitive {

Triangles::Triangles()
{
    _name = "triangles";
    _type = "triangles";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _p1 = Math::Point3D(-1, 0, -1);
    _p2 = Math::Point3D(1, 0, -1);
    _p3 = Math::Point3D(0, 1, 0);
    _normal = Math::Vector3D(0, 0, 1);
}

Triangles::Triangles(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3)
{
    _name = "triangles";
    _type = "triangles";
    setPoints(p1, p2, p3);
}

void Triangles::setPoints(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3)
{
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;

    _position = Math::Point3D(
        (p1._x + p2._x + p3._x) / 3.0,
        (p1._y + p2._y + p3._y) / 3.0,
        (p1._z + p2._z + p3._z) / 3.0
    );

    Math::Vector3D v1(_p2._x - _p1._x, _p2._y - _p1._y, _p2._z - _p1._z);
    Math::Vector3D v2(_p3._x - _p1._x, _p3._y - _p1._y, _p3._z - _p1._z);
    _normal = v1.cross(v2);
    _normal.normalize();
}

std::string &Triangles::getName()
{
    return _name;
}

std::string &Triangles::getType()
{
    return _type;
}

Math::Point3D &Triangles::getPosition()
{
    return _position;
}

Math::Vector3D &Triangles::getRotation()
{
    return _rotation;
}

Math::Vector3D Triangles::getNormal() const
{
    return _normal;
}

Math::hitdata_t Triangles::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    Math::Vector3D edge1(_p2._x - _p1._x, _p2._y - _p1._y, _p2._z - _p1._z);
    Math::Vector3D edge2(_p3._x - _p1._x, _p3._y - _p1._y, _p3._z - _p1._z);
    Math::Vector3D h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -0.00001 && a < 0.00001)
        return hitData;

    double f = 1.0 / a;
    Math::Vector3D s(ray.origin._x - _p1._x, ray.origin._y - _p1._y, ray.origin._z - _p1._z);
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return hitData;

    Math::Vector3D q = s.cross(edge1);
    double v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return hitData;

    double t = f * edge2.dot(q);

    if (t > 0.001) {
        hitData.hit = true;
        hitData.distance = t;
        hitData.point = Math::Point3D(
            ray.origin._x + t * ray.direction._x,
            ray.origin._y + t * ray.direction._y,
            ray.origin._z + t * ray.direction._z
        );
        hitData.normal = _normal;
        if (hitData.normal.dot(ray.direction) > 0) {
            hitData.normal = Math::Vector3D(-_normal._x, -_normal._y, -_normal._z);
        }
        hitData.color = {128.0, 0.0, 128.0, 1.0};
    }

    return hitData;
}

} // namespace Raytracer::primitive
