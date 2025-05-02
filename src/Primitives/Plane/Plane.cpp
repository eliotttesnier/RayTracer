//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <string>
#include "Plane.hpp"

namespace RayTracer::primitive {

Plane::Plane()
    : _name("plane"), _type("plane"), _position(0, 0, 0), _rotation(0, 0, 0),
      _width(1.0), _height(1.0),
      _rectangle(Math::Point3D(0, 0, 0), Math::Vector3D(_width, 0, 0), Math::Vector3D(0, 0, _height))
{
}

Plane::Plane(const Math::Point3D &position, const Math::Vector3D &rotation)
    : _name("plane"), _type("plane"), _position(position), _rotation(rotation),
      _width(1.0), _height(1.0),
      _rectangle(position, Math::Vector3D(_width, 0, 0), Math::Vector3D(0, 0, _height))
{
    _rectangle.rotateXSelf(_rotation._x);
    _rectangle.rotateYSelf(_rotation._y);
    _rectangle.rotateZSelf(_rotation._z);
}

std::string &Plane::getName()
{
    return _name;
}

std::string &Plane::getType()
{
    return _type;
}

Math::Point3D &Plane::getPosition()
{
    return _position;
}

Math::Vector3D &Plane::getRotation()
{
    return _rotation;
}

double Plane::getWidth() const
{
    return _width;
}

void Plane::setWidth(double width)
{
    _width = width;
    _rectangle = RayTracer::Rectangle3D(_position, Math::Vector3D(_width, 0, 0), Math::Vector3D(0, 0, _height));
    _rectangle.rotateXSelf(_rotation._x);
    _rectangle.rotateYSelf(_rotation._y);
    _rectangle.rotateZSelf(_rotation._z);
}

double Plane::getHeight() const
{
    return _height;
}

void Plane::setHeight(double height)
{
    _height = height;
    _rectangle = RayTracer::Rectangle3D(_position, Math::Vector3D(_width, 0, 0), Math::Vector3D(0, 0, _height));
    _rectangle.rotateXSelf(_rotation._x);
    _rectangle.rotateYSelf(_rotation._y);
    _rectangle.rotateZSelf(_rotation._z);
}

Math::hitdata_t Plane::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    double t, u, v;

    hitData.hit = _rectangle.hits(ray, t, u, v);
    if (hitData.hit) {
        hitData.distance = t;

        hitData.point = Math::Point3D(
            ray.origin._x + t * ray.direction._x,
            ray.origin._y + t * ray.direction._y,
            ray.origin._z + t * ray.direction._z
        );
        hitData.normal = _rectangle.getNormal();

        if (hitData.normal.dot(ray.direction) > 0) {
            hitData.normal = Math::Vector3D(
                -hitData.normal._x,
                -hitData.normal._y,
                -hitData.normal._z
            );
        }
    }

    hitData.color = {128.0, 128.0, 128.0, 1.0}; // Gray
    return hitData;
}

}
