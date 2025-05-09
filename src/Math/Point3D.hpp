/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_
#include <tuple>

namespace Math {
    class Vector3D;

    class Point3D {
        public:
            double _x;
            double _y;
            double _z;

            Point3D();
            Point3D(double x, double y, double z);
            Point3D(const std::tuple<double, double, double> &tuple);
            ~Point3D() = default;

            Point3D operator+(const Point3D &other) const;
            Point3D &operator+=(const Point3D &other);
            Point3D operator-(const Point3D &other) const;
            Point3D &operator-=(const Point3D &other);

            Point3D operator+(const Vector3D &vector) const;
            Point3D &operator+=(const Vector3D &vector);
            Point3D operator-(const Vector3D &vector) const;
            Point3D &operator-=(const Vector3D &vector);

            Point3D &operator=(const std::tuple<double, double, double> &tuple);

            Point3D translate(const Vector3D &translation) const;
            Point3D &translateSelf(const Vector3D &translation);

            Point3D rotateX(double degrees) const;
            Point3D &rotateXSelf(double degrees);

            Point3D rotateY(double degrees) const;
            Point3D &rotateYSelf(double degrees);

            Point3D rotateZ(double degrees) const;
            Point3D &rotateZSelf(double degrees);
    };
}

#endif /* !POINT3D_HPP_ */
