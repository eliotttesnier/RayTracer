/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Matrix4x4
*/

#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <array>
#include <cmath>
#include <iostream>

namespace Math {

class Matrix4x4 {
public:
    std::array<std::array<double, 4>, 4> data;

    Matrix4x4() : data({{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}}) {}

    Matrix4x4(const std::array<std::array<double, 4>, 4> &matrix) : data(matrix) {}

    Point3D multiplyPoint(const Point3D& point) const {
        double w = data[3][0] * point._x + data[3][1] * point._y + data[3][2] * point._z + data[3][3];
        if (std::abs(w) < 0.00001) w = 1.0;
        return Point3D(
            (data[0][0] * point._x + data[0][1] * point._y + data[0][2] * point._z + data[0][3]) / w,
            (data[1][0] * point._x + data[1][1] * point._y + data[1][2] * point._z + data[1][3]) / w,
            (data[2][0] * point._x + data[2][1] * point._y + data[2][2] * point._z + data[2][3]) / w
        );
    }

    Vector3D multiplyVector(const Vector3D& vector) const {
        return Vector3D(
            data[0][0] * vector._x + data[0][1] * vector._y + data[0][2] * vector._z,
            data[1][0] * vector._x + data[1][1] * vector._y + data[1][2] * vector._z,
            data[2][0] * vector._x + data[2][1] * vector._y + data[2][2] * vector._z
        );
    }

    Matrix4x4 multiply(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix4x4 operator*(const Matrix4x4& other) const {
        return multiply(other);
    }

    static Matrix4x4 createTranslation(double x, double y, double z) {
        Matrix4x4 result;
        result.data[0][3] = x;
        result.data[1][3] = y;
        result.data[2][3] = z;
        return result;
    }

    static Matrix4x4 createRotationX(double degrees) {
        double rad = degrees * M_PI / 180.0;
        double cos_val = cos(rad);
        double sin_val = sin(rad);
        Matrix4x4 result;
        result.data[1][1] = cos_val;
        result.data[1][2] = -sin_val;
        result.data[2][1] = sin_val;
        result.data[2][2] = cos_val;
        return result;
    }

    static Matrix4x4 createRotationY(double degrees) {
        double rad = degrees * M_PI / 180.0;
        double cos_val = cos(rad);
        double sin_val = sin(rad);
        Matrix4x4 result;
        result.data[0][0] = cos_val;
        result.data[0][2] = sin_val;
        result.data[2][0] = -sin_val;
        result.data[2][2] = cos_val;
        return result;
    }

    static Matrix4x4 createRotationZ(double degrees) {
        double rad = degrees * M_PI / 180.0;
        double cos_val = cos(rad);
        double sin_val = sin(rad);
        Matrix4x4 result;
        result.data[0][0] = cos_val;
        result.data[0][1] = -sin_val;
        result.data[1][0] = sin_val;
        result.data[1][1] = cos_val;
        return result;
    }

    static Matrix4x4 createRotationFromEuler(double x, double y, double z) {
        return createRotationX(x) * createRotationY(y) * createRotationZ(z);
    }

    static Matrix4x4 createScale(double x, double y, double z) {
        Matrix4x4 result;
        result.data[0][0] = x;
        result.data[1][1] = y;
        result.data[2][2] = z;
        return result;
    }

    static Matrix4x4 createPerspective(double fov, double aspectRatio, double nearPlane, double farPlane) {
        double tanHalfFov = tan((fov * M_PI / 180.0) / 2.0);
        
        Matrix4x4 result;
        result.data = {{{1.0 / (aspectRatio * tanHalfFov), 0, 0, 0},
                        {0, 1.0 / tanHalfFov, 0, 0},
                        {0, 0, -(farPlane + nearPlane) / (farPlane - nearPlane), -(2 * farPlane * nearPlane) / (farPlane - nearPlane)},
                        {0, 0, -1, 0}}};
        return result;
    }

    static Matrix4x4 createLookAt(const Point3D& eye, const Point3D& target, const Vector3D& up) {
        Vector3D f = Vector3D(target._x - eye._x, target._y - eye._y, target._z - eye._z).normalized();
        Vector3D s = f.cross(up).normalized();
        Vector3D u = s.cross(f);
        
        Matrix4x4 result;
        result.data = {{{s._x, s._y, s._z, -s.dot(Vector3D(eye._x, eye._y, eye._z))},
                        {u._x, u._y, u._z, -u.dot(Vector3D(eye._x, eye._y, eye._z))},
                        {-f._x, -f._y, -f._z, f.dot(Vector3D(eye._x, eye._y, eye._z))},
                        {0, 0, 0, 1}}};
        return result;
    }

    Matrix4x4 inverse() const {
        Matrix4x4 result;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.data[i][j] = data[j][i];
            }
        }
        
        for (int i = 0; i < 3; i++) {
            result.data[i][3] = 0;
            for (int j = 0; j < 3; j++) {
                result.data[i][3] -= result.data[i][j] * data[j][3];
            }
        }
        
        return result;
    }

    void print() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

}  // namespace Math

#endif /* !MATRIX4X4_HPP */
