#include <cmath>
#include <string>
#include "Cone.hpp"
namespace RayTracer::primitive {

Cone::Cone()
{
    _name = "cone";
    _type = "cone";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _height = 1.0;
}

Cone::Cone(const Math::Point3D &position, double radius, double height)
{
    _name = "cone";
    _type = "cone";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _height = height;
}

std::string &Cone::getName()
{
    return _name;
}

std::string &Cone::getType()
{
    return _type;
}

Math::Point3D &Cone::getPosition()
{
    return _position;
}

Math::Vector3D &Cone::getRotation()
{
    return _rotation;
}

double Cone::getRadius() const
{
    return _radius;
}

void Cone::setRadius(double radius)
{
    _radius = radius;
}

double Cone::getHeight() const
{
    return _height;
}

void Cone::setHeight(double height)
{
    _height = height;
}

Math::Vector3D Cone::normalAt(const Math::Point3D& point) const
{
    double dx = point._x - _position._x;
    double dz = point._z - _position._z;
    double dy = point._y - _position._y;

    double k = _radius / _height;

    Math::Vector3D normal(2 * dx, -2 * (k * k) * dy, 2 * dz);
    normal.normalize();
    return normal;
}

Math::hitdata_t Cone::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;

    // Cone surface intersection
    double k = _radius / _height;
    k = k * k;

    Math::Vector3D oc(ray.origin._x - _position._x,
                     ray.origin._y - _position._y,
                     ray.origin._z - _position._z);

    double a = ray.direction._x * ray.direction._x -
               k * ray.direction._y * ray.direction._y +
               ray.direction._z * ray.direction._z;

    double b = 2.0 * (oc._x * ray.direction._x -
                      k * oc._y * ray.direction._y +
                      oc._z * ray.direction._z);

    double c = oc._x * oc._x -
               k * oc._y * oc._y +
               oc._z * oc._z;

    double discriminant = b * b - 4 * a * c;
    double cone_t = std::numeric_limits<double>::infinity();

    if (discriminant >= 0) {
        double sqrtd = sqrt(discriminant);
        double t1 = (-b - sqrtd) / (2.0 * a);
        double t2 = (-b + sqrtd) / (2.0 * a);

        double y1 = ray.origin._y + t1 * ray.direction._y - _position._y;
        double y2 = ray.origin._y + t2 * ray.direction._y - _position._y;

        if (y1 >= 0 && y1 <= _height && t1 > 0.001) {
            cone_t = t1;
        } else if (y2 >= 0 && y2 <= _height && t2 > 0.001) {
            cone_t = t2;
        }
    }

    // Base circle intersection
    double base_t = std::numeric_limits<double>::infinity();
    if (std::abs(ray.direction._y) > 0.001) {
        double t = (_position._y - ray.origin._y) / ray.direction._y;
        if (t > 0.001) {
            double x = ray.origin._x + t * ray.direction._x - _position._x;
            double z = ray.origin._z + t * ray.direction._z - _position._z;
            if (x * x + z * z <= _radius * _radius) {
                base_t = t;
            }
        }
    }

    // Use the closest intersection
    double t = std::min(cone_t, base_t);
    if (std::isfinite(t)) {
        hitData.hit = true;
        hitData.distance = t;
        hitData.point = Math::Point3D(
            ray.origin._x + t * ray.direction._x,
            ray.origin._y + t * ray.direction._y,
            ray.origin._z + t * ray.direction._z
        );
        
        if (t == base_t) {
            hitData.normal = Math::Vector3D(0, -1, 0);
        } else {
            hitData.normal = normalAt(hitData.point);
        }
    }

    hitData.color = {0.0, 255.0, 0.0, 1.0};
    return hitData;
}

}  // namespace Raytracer::primitive
