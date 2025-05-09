/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Point3D
*/

#include <cmath>
#include <tuple>

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Math
{
Point3D::Point3D() : _x(0), _y(0), _z(0)
{
}

Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

Point3D::Point3D(const std::tuple<double, double, double> &tuple)
{
    _x = std::get<0>(tuple);
    _y = std::get<1>(tuple);
    _z = std::get<2>(tuple);
}

Point3D Point3D::operator+(const Point3D &other) const
{
    return Point3D(_x + other._x, _y + other._y, _z + other._z);
}

Point3D &Point3D::operator+=(const Point3D &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Point3D Point3D::operator-(const Point3D &other) const
{
    return Point3D(_x - other._x, _y - other._y, _z - other._z);
}

Point3D &Point3D::operator-=(const Point3D &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

Point3D Point3D::operator+(const Vector3D &vector) const
{
    return Point3D(_x + vector._x, _y + vector._y, _z + vector._z);
}

Point3D &Point3D::operator+=(const Vector3D &vector)
{
    _x += vector._x;
    _y += vector._y;
    _z += vector._z;
    return *this;
}

Point3D Point3D::operator-(const Vector3D &vector) const
{
    return Point3D(_x - vector._x, _y - vector._y, _z - vector._z);
}

Point3D &Point3D::operator-=(const Vector3D &vector)
{
    _x -= vector._x;
    _y -= vector._y;
    _z -= vector._z;
    return *this;
}

Point3D & Point3D::operator=(const std::tuple<double, double, double> &tuple) {
    _x = std::get<0>(tuple);
    _y = std::get<1>(tuple);
    _z = std::get<2>(tuple);
    return *this;
}

Point3D Point3D::translate(const Vector3D &translation) const
{
    return Point3D(_x + translation._x, _y + translation._y, _z + translation._z);
}

Point3D &Point3D::translateSelf(const Vector3D &translation)
{
    _x += translation._x;
    _y += translation._y;
    _z += translation._z;
    return *this;
}

Point3D Point3D::rotateX(double degrees) const
{
    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_y = _y * cosA - _z * sinA;
    double new_z = _y * sinA + _z * cosA;

    return Point3D(_x, new_y, new_z);
}

Point3D &Point3D::rotateXSelf(double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_y = _y * cosA - _z * sinA;
    double new_z = _y * sinA + _z * cosA;

    _y = new_y;
    _z = new_z;

    return *this;
}

Point3D Point3D::rotateY(double degrees) const
{
    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = _x * cosA + _z * sinA;
    double new_z = -_x * sinA + _z * cosA;

    return Point3D(new_x, _y, new_z);
}

Point3D &Point3D::rotateYSelf(double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = _x * cosA + _z * sinA;
    double new_z = -_x * sinA + _z * cosA;

    _x = new_x;
    _z = new_z;

    return *this;
}

Point3D Point3D::rotateZ(double degrees) const
{
    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = _x * cosA - _y * sinA;
    double new_y = _x * sinA + _y * cosA;

    return Point3D(new_x, new_y, _z);
}

Point3D &Point3D::rotateZSelf(double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = cos(radians);
    double sinA = sin(radians);

    double new_x = _x * cosA - _y * sinA;
    double new_y = _x * sinA + _y * cosA;

    _x = new_x;
    _y = new_y;

    return *this;
}
}
