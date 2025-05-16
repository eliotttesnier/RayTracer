/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Rectangle
*/

#include <cmath>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>
#include "Rectangle.hpp"

namespace RayTracer::primitive {

Rectangle::Rectangle()
{
    _name = "rectangle";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _length = 1.0;
    _width = 1.0;
    _height = 1.0;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_length/2.0, -_height/2.0, -_width/2.0);
    _boundingBox.max = Math::Point3D(_length/2.0, _height/2.0, _width/2.0);
}

Rectangle::Rectangle(const Math::Point3D &position, double length, double width, double height)
{
    _name = "rectangle";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _length = length;
    _width = width;
    _height = height;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_length/2.0, -_height/2.0, -_width/2.0);
    _boundingBox.max = Math::Point3D(_length/2.0, _height/2.0, _width/2.0);
}

double Rectangle::getLength() const
{
    return _length;
}

double Rectangle::getWidth() const
{
    return _width;
}

double Rectangle::getHeight() const
{
    return _height;
}

void Rectangle::setLength(double length)
{
    _length = length;
    _boundingBox.min._x = -_length/2.0;
    _boundingBox.max._x = _length/2.0;
}

void Rectangle::setWidth(double width)
{
    _width = width;
    _boundingBox.min._z = -_width/2.0;
    _boundingBox.max._z = _width/2.0;
}

void Rectangle::setHeight(double height)
{
    _height = height;
    _boundingBox.min._y = -_height/2.0;
    _boundingBox.max._y = _height/2.0;
}

Math::Vector3D Rectangle::normalAt(const Math::Point3D& point) const
{
    Math::Point3D localPoint = transformPointToLocal(point);

    double dxMin = std::abs(localPoint._x - _boundingBox.min._x);
    double dxMax = std::abs(localPoint._x - _boundingBox.max._x);
    double dyMin = std::abs(localPoint._y - _boundingBox.min._y);
    double dyMax = std::abs(localPoint._y - _boundingBox.max._y);
    double dzMin = std::abs(localPoint._z - _boundingBox.min._z);
    double dzMax = std::abs(localPoint._z - _boundingBox.max._z);

    double minDistance = std::min({dxMin, dxMax, dyMin, dyMax, dzMin, dzMax});

    Math::Vector3D localNormal;
    if (minDistance == dxMin)
        localNormal = Math::Vector3D(-1, 0, 0);
    else if (minDistance == dxMax)
        localNormal = Math::Vector3D(1, 0, 0);
    else if (minDistance == dyMin)
        localNormal = Math::Vector3D(0, -1, 0);
    else if (minDistance == dyMax)
        localNormal = Math::Vector3D(0, 1, 0);
    else if (minDistance == dzMin)
        localNormal = Math::Vector3D(0, 0, -1);
    else
        localNormal = Math::Vector3D(0, 0, 1);

    return transformNormalToWorld(localNormal);
}

Math::hitdata_t Rectangle::calculateRectangleIntersection(const Math::Ray &localRay) const
{
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.distance = std::numeric_limits<double>::max();

    double t_min = (-_length/2.0 - localRay.origin._x) / localRay.direction._x;
    double t_max = (_length/2.0 - localRay.origin._x) / localRay.direction._x;

    if (t_min > t_max)
        std::swap(t_min, t_max);

    double t_y_min = (-_height/2.0 - localRay.origin._y) / localRay.direction._y;
    double t_y_max = (_height/2.0 - localRay.origin._y) / localRay.direction._y;

    if (t_y_min > t_y_max)
        std::swap(t_y_min, t_y_max);

    if (t_min > t_y_max || t_y_min > t_max)
        return hitData;

    if (t_y_min > t_min)
        t_min = t_y_min;
    if (t_y_max < t_max)
        t_max = t_y_max;

    double t_z_min = (-_width/2.0 - localRay.origin._z) / localRay.direction._z;
    double t_z_max = (_width/2.0 - localRay.origin._z) / localRay.direction._z;

    if (t_z_min > t_z_max)
        std::swap(t_z_min, t_z_max);

    if (t_min > t_z_max || t_z_min > t_max)
        return hitData;

    if (t_z_min > t_min)
        t_min = t_z_min;
    if (t_z_max < t_max)
        t_max = t_z_max;

    double t = (t_min < 0.001) ? t_max : t_min;

    if (t < 0.001)
        return hitData;

    hitData.hit = true;
    hitData.distance = t;
    hitData.point = Math::Point3D(
        localRay.origin._x + t * localRay.direction._x,
        localRay.origin._y + t * localRay.direction._y,
        localRay.origin._z + t * localRay.direction._z
    );

    return hitData;
}

Math::hitdata_t Rectangle::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);

    Math::hitdata_t hitData = calculateRectangleIntersection(localRay);

    if (hitData.hit) {
        hitData.point = transformPointToWorld(hitData.point);
        hitData.normal = normalAt(hitData.point);
        hitData.color = _color;
    }

    return hitData;
}

Graphic::color_t Rectangle::getColor(
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
