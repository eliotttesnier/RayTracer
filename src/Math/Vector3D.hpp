/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include <tuple>

namespace Math
{
    class Vector3D
    {
        public:
            double _x;
            double _y;
            double _z;

            Vector3D();
            Vector3D(double x, double y, double z);
            Vector3D(const std::tuple<double, double, double> &tuple);
            ~Vector3D() = default;
            
            double length() const;
            double dot(const Vector3D &other) const;
            Vector3D cross(const Vector3D &other) const;
            
            Vector3D operator+(const Vector3D &other) const;
            Vector3D &operator+=(const Vector3D &other);
            Vector3D operator-(const Vector3D &other) const;
            Vector3D &operator-=(const Vector3D &other);
            Vector3D operator*(const Vector3D &other) const;
            Vector3D &operator*=(const Vector3D &other);
            Vector3D operator/(const Vector3D &other) const;
            Vector3D &operator/=(const Vector3D &other);
            
            Vector3D &operator=(const Vector3D &other);
            Vector3D &operator=(const std::tuple<double, double, double> &tuple);

            Vector3D operator*(double scalar) const;
            Vector3D &operator*=(double scalar);
            Vector3D operator/(double scalar) const;
            Vector3D &operator/=(double scalar);

            Vector3D operator-() const;

            Vector3D normalized() const;
            void normalize();
    };
}

#endif /* !VECTOR3D_HPP_ */
