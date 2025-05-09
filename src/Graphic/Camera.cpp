/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Camera
*/

#include "Camera.hpp"
#include <cmath>
#include <tuple>
#include <iostream>

namespace RayTracer {
Camera::Camera()
: origin(0, 0, 0), fov(75)
{
    Math::Point3D screenOrigin(0, 0, -1);
    Math::Vector3D bottom(1, 0, 0);
    Math::Vector3D left(0, 1, 0);

    screen = Rectangle3D(screenOrigin, bottom, left);
    resolution = std::make_tuple(1920, 1080);
    transformMatrix = Math::Matrix4x4();
}

Camera::Camera(const Math::Point3D &origin, const Rectangle3D &screen)
: origin(origin), screen(screen), resolution(1920, 1080), fov(75)
{
    transformMatrix = Math::Matrix4x4();
}

Camera::Camera(const Camera &other)
: origin(other.origin), screen(other.screen), resolution(other.resolution),
fov(other.fov), transformMatrix(other.transformMatrix)
{
}

Camera &Camera::operator=(const Camera &other)
{
    if (this != &other) {
        origin = other.origin;
        screen = other.screen;
        resolution = other.resolution;
        fov = other.fov;
        transformMatrix = other.transformMatrix;
    }
    return *this;
}

void Camera::rotateX(double degrees)
{
    screen.rotateXSelf(degrees);

    Math::Matrix4x4 rotationMatrix = Math::Matrix4x4::createRotationX(degrees);
    transformMatrix = rotationMatrix.multiply(transformMatrix);
}

void Camera::rotateY(double degrees)
{
    screen.rotateYSelf(degrees);

    Math::Matrix4x4 rotationMatrix = Math::Matrix4x4::createRotationY(degrees);
    transformMatrix = rotationMatrix.multiply(transformMatrix);
}

void Camera::rotateZ(double degrees)
{
    screen.rotateZSelf(degrees);

    Math::Matrix4x4 rotationMatrix = Math::Matrix4x4::createRotationZ(degrees);
    transformMatrix = rotationMatrix.multiply(transformMatrix);
}

void Camera::tilt(double degrees)
{
    rotateX(degrees);
}

void Camera::pan(double degrees)
{
    rotateY(degrees);
}

void Camera::roll(double degrees)
{
    rotateZ(degrees);
}

void Camera::setPosition(double x, double y, double z)
{
    origin = Math::Point3D(x, y, z);

    Math::Matrix4x4 translationMatrix = Math::Matrix4x4::createTranslation(x, y, z);
    for (int i = 0; i < 3; i++) {
        transformMatrix.data[i][3] = translationMatrix.data[i][3];
    }
}

Math::Point3D Camera::getPosition() const
{
    return origin;
}

void Camera::setRotation(double x, double y, double z)
{
    Math::Point3D screenOrigin(0, 0, -1);
    Math::Vector3D bottom(1, 0, 0);
    Math::Vector3D left(0, 1, 0);
    screen = Rectangle3D(screenOrigin, bottom, left);

    rotateZ(z);
    rotateY(y);
    rotateX(x);

    updateTransformMatrix();
}

void Camera::updateTransformMatrix()
{
    Math::Matrix4x4 rotationMatrix;

    Math::Vector3D right = screen.bottom_side.normalized();
    Math::Vector3D up = screen.left_side.normalized();
    Math::Vector3D forward = Math::Vector3D(screen.getNormal()).normalized();

    rotationMatrix.data[0][0] = right._x;
    rotationMatrix.data[1][0] = right._y;
    rotationMatrix.data[2][0] = right._z;

    rotationMatrix.data[0][1] = up._x;
    rotationMatrix.data[1][1] = up._y;
    rotationMatrix.data[2][1] = up._z;

    rotationMatrix.data[0][2] = forward._x;
    rotationMatrix.data[1][2] = forward._y;
    rotationMatrix.data[2][2] = forward._z;

    rotationMatrix.data[0][3] = origin._x;
    rotationMatrix.data[1][3] = origin._y;
    rotationMatrix.data[2][3] = origin._z;

    transformMatrix = rotationMatrix;
}

std::tuple<int, int> Camera::getResolution() const
{
    return resolution;
}

double Camera::getFov() const
{
    return fov;
}

Math::Ray Camera::ray(double u, double v) const
{
    double aspectRatio = static_cast<double>(std::get<0>(resolution)) /
        std::get<1>(resolution);

    double tanHalfFov = tan((fov * M_PI / 180.0) / 2.0);

    double scaledU = u * aspectRatio * tanHalfFov;
    double scaledV = v * tanHalfFov;

    Math::Point3D pointOnScreen = Math::Point3D(scaledU, scaledV, -1.0);

    Math::Point3D transformedPoint = transformMatrix.multiplyPoint(pointOnScreen);

    Math::Vector3D direction(
        transformedPoint._x - origin._x,
        transformedPoint._y - origin._y,
        transformedPoint._z - origin._z
    );
    direction.normalize();

    return Math::Ray(origin, direction);
}
}
