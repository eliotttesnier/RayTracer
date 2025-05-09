//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "Plane.hpp"

namespace RayTracer::primitive {

Plane::Plane()
{
    _name = "plane";
    _type = "plane";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _width = 1.0;
    _height = 1.0;
    _rectangle = RayTracer::Rectangle3D(_position,
                                        Math::Vector3D(_width, 0, 0),
                                        Math::Vector3D(0, 0, _height));
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_width/2.0, -0.001, -_height/2.0);
    _boundingBox.max = Math::Point3D(_width/2.0, 0.001, _height/2.0);
}

Plane::Plane(const Math::Point3D &position,
             const Math::Vector3D &rotation,
             std::tuple<double, double> size)
{
    _name = "plane";
    _type = "plane";
    _position = position;
    _rotation = rotation;
    _width = std::get<0>(size);
    _height = std::get<1>(size);
    _rectangle = RayTracer::Rectangle3D(_position,
                                        Math::Vector3D(_width, 0, 0),
                                        Math::Vector3D(0, 0, _height));
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_width/2.0, -0.001, -_height/2.0);
    _boundingBox.max = Math::Point3D(_width/2.0, 0.001, _height/2.0);
}

double Plane::getWidth() const
{
    return _width;
}

void Plane::setWidth(double width)
{
    _width = width;
    _rectangle = RayTracer::Rectangle3D(_position,
                                        Math::Vector3D(_width, 0, 0),
                                        Math::Vector3D(0, 0, _height));
    _boundingBox.min._x = -_width/2.0;
    _boundingBox.max._x = _width/2.0;
}

double Plane::getHeight() const
{
    return _height;
}

void Plane::setHeight(double height)
{
    _height = height;
    _rectangle = RayTracer::Rectangle3D(_position,
                                        Math::Vector3D(_width, 0, 0),
                                        Math::Vector3D(0, 0, _height));
    _boundingBox.min._z = -_height/2.0;
    _boundingBox.max._z = _height/2.0;
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

    if (!_boundingBox.intersect(localRay))
        return hitData;

    if (std::abs(localRay.direction._y) > 0.001) {
        double t = -localRay.origin._y / localRay.direction._y;

        if (t > 0.001) {
            double x = localRay.origin._x + t * localRay.direction._x;
            double z = localRay.origin._z + t * localRay.direction._z;

            if (std::abs(x) <= _width/2.0 && std::abs(z) <= _height/2.0) {
                hitData.hit = true;
                hitData.distance = t;

                Math::Point3D localHitPoint(x, 0, z);

                hitData.point = transformPointToWorld(localHitPoint);
                hitData.normal = normalAt(hitData.point);
                if (hitData.normal.dot(ray.direction) > 0) {
                    hitData.normal = Math::Vector3D(
                        -hitData.normal._x,
                        -hitData.normal._y,
                        -hitData.normal._z
                    );
                }
            }
        }
    }

    hitData.color = {128.0, 128.0, 128.0, 1.0};  // Gray
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
