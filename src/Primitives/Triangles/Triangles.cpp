/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** Triangles
*/

#include <cmath>
#include <vector>
#include "Triangles.hpp"

namespace RayTracer::primitive {

Triangles::Triangles()
{
    _name = "triangles";    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _p1 = Math::Point3D(-1, 0, -1);
    _p2 = Math::Point3D(1, 0, -1);
    _p3 = Math::Point3D(0, 1, 0);
    _normal = Math::Vector3D(0, 0, 1);
}

Triangles::Triangles(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3)
{
    _name = "triangles";
    setPoints(p1, p2, p3);
}

void Triangles::setPoints(const Math::Point3D &p1,
                          const Math::Point3D &p2,
                          const Math::Point3D &p3)
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

void Triangles::setAnchorPoint(const Math::Vector3D &anchorPoint)
{
    _anchorPoint = anchorPoint - Math::Vector3D(_position._x, _position._y, _position._z);
}

Math::Vector3D Triangles::getNormal() const
{
    return _normal;
}

Math::Vector3D Triangles::normalAt(const Math::Point3D& point) const
{
    return transformNormalToWorld(_normal);
}

Math::hitdata_t Triangles::calculateTriangleIntersection(const Math::Ray &localRay) const
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    Math::Point3D v1 = _p1 - Math::Vector3D(_position._x, _position._y, _position._z);
    Math::Point3D v2 = _p2 - Math::Vector3D(_position._x, _position._y, _position._z);
    Math::Point3D v3 = _p3 - Math::Vector3D(_position._x, _position._y, _position._z);

    Math::Vector3D edge1(v2._x - v1._x, v2._y - v1._y, v2._z - v1._z);
    Math::Vector3D edge2(v3._x - v1._x, v3._y - v1._y, v3._z - v1._z);
    Math::Vector3D h = localRay.direction.cross(edge2);
    double a = edge1.dot(h);

    if (a > -0.00001 && a < 0.00001)
        return hitData;

    double f = 1.0 / a;
    Math::Vector3D s(localRay.origin._x - v1._x,
        localRay.origin._y - v1._y, localRay.origin._z - v1._z);
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return hitData;

    Math::Vector3D q = s.cross(edge1);
    double v = f * localRay.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return hitData;

    double t = f * edge2.dot(q);

    if (t > 0.001) {
        hitData.hit = true;
        hitData.distance = t;

        Math::Point3D localHitPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        hitData.point = transformPointToWorld(localHitPoint);

        Math::Vector3D localNormal = _normal;
        if (localNormal.dot(localRay.direction) > 0) {
            localNormal = Math::Vector3D(-localNormal._x, -localNormal._y, -localNormal._z);
        }
        hitData.normal = transformNormalToWorld(localNormal);

        hitData.color = _color;
    }

    return hitData;
}

Math::hitdata_t Triangles::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);

    return calculateTriangleIntersection(localRay);
}

Graphic::color_t Triangles::getColor(
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
