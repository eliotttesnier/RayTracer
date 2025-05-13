//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "Plane.hpp"

namespace RayTracer::primitive {

Plane::Plane()
{
    _name = "plane";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);

    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-1e6, -1.0, -1e6);
    _boundingBox.max = Math::Point3D(1e6, 1.0, 1e6);
}

Plane::Plane(const Math::Point3D &position, const Math::Vector3D &rotation)
{
    _name = "plane";
    _position = position;
    _rotation = rotation;

    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-1e6, -1.0, -1e6);
    _boundingBox.max = Math::Point3D(1e6, 1.0, 1e6);
}

Math::Vector3D Plane::normalAt(const Math::Point3D& point) const
{
    Math::Vector3D localNormal(0, 1, 0);
    return transformNormalToWorld(localNormal);
}

Math::hitdata_t Plane::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);
    Math::hitdata_t hitData;
    hitData.hit = false;

    if (std::abs(localRay.direction._y) > 0.001) {
        double t = -localRay.origin._y / localRay.direction._y;

        if (t > 0.001) {
            hitData.hit = true;
            hitData.distance = t;

            Math::Point3D localHitPoint = localRay.origin + localRay.direction * t;
            hitData.point = transformPointToWorld(localHitPoint);
            hitData.normal = normalAt(hitData.point);

            if (hitData.normal.dot(ray.direction) > 0) {
                hitData.normal = -hitData.normal;
            }

            hitData.color = _color;
        }
    }

    return hitData;
}

Graphic::color_t Plane::getColor(
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
