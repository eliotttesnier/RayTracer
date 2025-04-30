#include <cmath>
#include "Cylinder.hpp"

namespace Raytracer::primitive {

Cylinder::Cylinder()
{
    _name = "cylinder";
    _type = "cylinder";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _height = 1.0;
}

Cylinder::Cylinder(const Math::Point3D &position, double radius, double height)
{
    _name = "cylinder";
    _type = "cylinder";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _height = height;
}

std::string &Cylinder::getName()
{
    return _name;
}

std::string &Cylinder::getType()
{
    return _type;
}

Math::Point3D &Cylinder::getPosition()
{
    return _position;
}

Math::Vector3D &Cylinder::getRotation()
{
    return _rotation;
}

double Cylinder::getRadius() const
{
    return _radius;
}

void Cylinder::setRadius(double radius)
{
    _radius = radius;
}

double Cylinder::getHeight() const
{
    return _height;
}

void Cylinder::setHeight(double height)
{
    _height = height;
}

Math::Vector3D Cylinder::normalAt(const Math::Point3D& point) const
{
    double dx = point._x - _position._x;
    double dz = point._z - _position._z;
    Math::Vector3D normal(dx, 0, dz);
    normal.normalize();
    return normal;
}

Math::hitdata_t Cylinder::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    Math::Vector3D oc(ray.origin._x - _position._x, 0,
                     ray.origin._z - _position._z);

    Math::Vector3D dir(ray.direction._x, 0, ray.direction._z);

    double a = dir.dot(dir);
    double b = 2.0 * oc.dot(dir);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitData;

    double sqrtd = sqrt(discriminant);
    double t1 = (-b - sqrtd) / (2.0 * a);
    double t2 = (-b + sqrtd) / (2.0 * a);

    double y1 = ray.origin._y + t1 * ray.direction._y;
    double y2 = ray.origin._y + t2 * ray.direction._y;

    if ((y1 < _position._y || y1 > _position._y + _height) &&
        (y2 < _position._y || y2 > _position._y + _height))
        return hitData;

    double t = (t1 < t2 && y1 >= _position._y && y1 <= _position._y + _height) ? t1 : t2;

    if (t > 0.001) {
        hitData.hit = true;
        hitData.distance = t;
        hitData.point = Math::Point3D(
            ray.origin._x + t * ray.direction._x,
            ray.origin._y + t * ray.direction._y,
            ray.origin._z + t * ray.direction._z
        );
        hitData.normal = normalAt(hitData.point);
    }
    return hitData;
}

}
