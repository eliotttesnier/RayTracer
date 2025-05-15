/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include <cmath>
#include <tuple>

namespace Math
{
Vector3D::Vector3D() : _x(0), _y(0), _z(0)
{
}

Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

Vector3D::Vector3D(const std::tuple<double, double, double> &tuple)
{
    _x = std::get<0>(tuple);
    _y = std::get<1>(tuple);
    _z = std::get<2>(tuple);
}

double Vector3D::length() const
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

double Vector3D::dot(const Vector3D &other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(_x + other._x, _y + other._y, _z + other._z);
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(_x - other._x, _y - other._y, _z - other._z);
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

Vector3D Vector3D::operator*(const Vector3D &other) const
{
    return Vector3D(_x * other._x, _y * other._y, _z * other._z);
}

Vector3D &Vector3D::operator*=(const Vector3D &other)
{
    _x *= other._x;
    _y *= other._y;
    _z *= other._z;
    return *this;
}

Vector3D Vector3D::operator/(const Vector3D &other) const
{
    return Vector3D(_x / other._x, _y / other._y, _z / other._z);
}

Vector3D &Vector3D::operator/=(const Vector3D &other)
{
    _x /= other._x;
    _y /= other._y;
    _z /= other._z;
    return *this;
}

Vector3D &Vector3D::operator=(const Vector3D &other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

Vector3D & Vector3D::operator=(const std::tuple<double, double, double> &tuple) {
    _x = std::get<0>(tuple);
    _y = std::get<1>(tuple);
    _z = std::get<2>(tuple);
    return *this;
}

Vector3D Vector3D::operator*(double scalar) const
{
    return Vector3D(_x * scalar, _y * scalar, _z * scalar);
}

Vector3D &Vector3D::operator*=(double scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const
{
    return Vector3D(_x / scalar, _y / scalar, _z / scalar);
}

Vector3D &Vector3D::operator/=(double scalar)
{
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
    return *this;
}

Vector3D Vector3D::normalized() const
{
    double len = length();
    if (len < 1e-8)
        return Vector3D(0, 0, 0);
    return Vector3D(_x / len, _y / len, _z / len);
}

void Vector3D::normalize()
{
    double len = length();
    if (len < 1e-8)
        return;
    _x /= len;
    _y /= len;
    _z /= len;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(
        _y * other._z - _z * other._y,
        _z * other._x - _x * other._z,
        _x * other._y - _y * other._x
    );
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-_x, -_y, -_z);
}
}
