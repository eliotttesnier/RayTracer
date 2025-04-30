/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"
#include <cmath>

namespace RayTracer {
Rectangle3D::Rectangle3D()
    : origin(0, 0, 0), bottom_side(1, 0, 0), left_side(0, 1, 0)
{
}

Rectangle3D::Rectangle3D(const Math::Point3D &origin, const Math::Vector3D &bottom_side, const Math::Vector3D &left_side)
    : origin(origin), bottom_side(bottom_side), left_side(left_side)
{
}

Math::Point3D Rectangle3D::pointAt(double u, double v) const
{
    return Math::Point3D(
        origin._x + u * bottom_side._x + v * left_side._x,
        origin._y + u * bottom_side._y + v * left_side._y,
        origin._z + u * bottom_side._z + v * left_side._z
    );
}

Math::Vector3D Rectangle3D::getNormal() const
{
    // The normal is the cross product of the two edges
    Math::Vector3D normal = bottom_side.cross(left_side);
    
    // Normalize the vector manually
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

bool Rectangle3D::hits(const Math::Ray &ray, double &t, double &u, double &v) const
{
    Math::Vector3D normal = getNormal();
    double denominator = normal.dot(ray.direction);

    if (std::abs(denominator) < 1e-8)
        return false;

    bool flipNormal = denominator > 0;
    if (flipNormal) {
        normal = Math::Vector3D(-normal._x, -normal._y, -normal._z);
        denominator = -denominator;
    }

    double d = -normal.dot(Math::Vector3D(origin._x, origin._y, origin._z));
    t = -(normal.dot(Math::Vector3D(ray.origin._x, ray.origin._y, ray.origin._z)) + d) / denominator;

    if (t < 0.001)
        return false;

    Math::Point3D intersection(
        ray.origin._x + t * ray.direction._x,
        ray.origin._y + t * ray.direction._y,
        ray.origin._z + t * ray.direction._z
    );

    Math::Vector3D v0(
        origin._x - intersection._x,
        origin._y - intersection._y,
        origin._z - intersection._z
    );

    double dotV0Bottom = v0.dot(bottom_side);
    double dotV0Left = v0.dot(left_side);
    double dotBottomBottom = bottom_side.dot(bottom_side);
    double dotLeftLeft = left_side.dot(left_side);

    u = -dotV0Bottom / dotBottomBottom;
    v = -dotV0Left / dotLeftLeft;

    return (u >= 0 && u <= 1 && v >= 0 && v <= 1);
}

Rectangle3D Rectangle3D::translate(const Math::Vector3D &translation) const
{
    Math::Point3D newOrigin = origin;
    newOrigin += translation;
    return Rectangle3D(newOrigin, bottom_side, left_side);
}

Rectangle3D &Rectangle3D::translateSelf(const Math::Vector3D &translation)
{
    origin += translation;
    return *this;
}

Rectangle3D Rectangle3D::rotateX(double degrees) const
{
    Math::Point3D newOrigin = origin.rotateX(degrees);
    Math::Vector3D newBottom = bottom_side;
    Math::Vector3D newLeft = left_side;

    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_y = newBottom._y * cosA - newBottom._z * sinA;
    double new_z = newBottom._y * sinA + newBottom._z * cosA;
    newBottom._y = new_y;
    newBottom._z = new_z;

    new_y = newLeft._y * cosA - newLeft._z * sinA;
    new_z = newLeft._y * sinA + newLeft._z * cosA;
    newLeft._y = new_y;
    newLeft._z = new_z;

    return Rectangle3D(newOrigin, newBottom, newLeft);
}

Rectangle3D &Rectangle3D::rotateXSelf(double degrees)
{
    origin.rotateXSelf(degrees);

    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_y = bottom_side._y * cosA - bottom_side._z * sinA;
    double new_z = bottom_side._y * sinA + bottom_side._z * cosA;
    bottom_side._y = new_y;
    bottom_side._z = new_z;

    new_y = left_side._y * cosA - left_side._z * sinA;
    new_z = left_side._y * sinA + left_side._z * cosA;
    left_side._y = new_y;
    left_side._z = new_z;

    return *this;
}

Rectangle3D Rectangle3D::rotateY(double degrees) const
{
    Math::Point3D newOrigin = origin.rotateY(degrees);
    Math::Vector3D newBottom = bottom_side;
    Math::Vector3D newLeft = left_side;

    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = newBottom._x * cosA + newBottom._z * sinA;
    double new_z = -newBottom._x * sinA + newBottom._z * cosA;
    newBottom._x = new_x;
    newBottom._z = new_z;

    new_x = newLeft._x * cosA + newLeft._z * sinA;
    new_z = -newLeft._x * sinA + newLeft._z * cosA;
    newLeft._x = new_x;
    newLeft._z = new_z;

    return Rectangle3D(newOrigin, newBottom, newLeft);
}

Rectangle3D &Rectangle3D::rotateYSelf(double degrees)
{
    origin.rotateYSelf(degrees);

    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = bottom_side._x * cosA + bottom_side._z * sinA;
    double new_z = -bottom_side._x * sinA + bottom_side._z * cosA;
    bottom_side._x = new_x;
    bottom_side._z = new_z;

    new_x = left_side._x * cosA + left_side._z * sinA;
    new_z = -left_side._x * sinA + left_side._z * cosA;
    left_side._x = new_x;
    left_side._z = new_z;

    return *this;
}

Rectangle3D Rectangle3D::rotateZ(double degrees) const
{
    Math::Point3D newOrigin = origin.rotateZ(degrees);
    Math::Vector3D newBottom = bottom_side;
    Math::Vector3D newLeft = left_side;

    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = newBottom._x * cosA - newBottom._y * sinA;
    double new_y = newBottom._x * sinA + newBottom._y * cosA;
    newBottom._x = new_x;
    newBottom._y = new_y;

    new_x = newLeft._x * cosA - newLeft._y * sinA;
    new_y = newLeft._x * sinA + newLeft._y * cosA;
    newLeft._x = new_x;
    newLeft._y = new_y;

    return Rectangle3D(newOrigin, newBottom, newLeft);
}

Rectangle3D &Rectangle3D::rotateZSelf(double degrees)
{
    origin.rotateZSelf(degrees);

    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = bottom_side._x * cosA - bottom_side._y * sinA;
    double new_y = bottom_side._x * sinA + bottom_side._y * cosA;
    bottom_side._x = new_x;
    bottom_side._y = new_y;

    new_x = left_side._x * cosA - left_side._y * sinA;
    new_y = left_side._x * sinA + left_side._y * cosA;
    left_side._x = new_x;
    left_side._y = new_y;

    return *this;
}
}
