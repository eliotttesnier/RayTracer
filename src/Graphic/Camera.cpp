/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Camera
*/

#include "Camera.hpp"
#include <cmath>

namespace RayTracer {
Camera::Camera()
    : origin(0, 0, 0)
{
    Math::Point3D screenOrigin(-1, -1, -1);
    Math::Vector3D bottom(2, 0, 0);
    Math::Vector3D left(0, 2, 0);

    screen = Rectangle3D(screenOrigin, bottom, left);
}

Camera::Camera(const Math::Point3D &origin, const Rectangle3D &screen)
    : origin(origin), screen(screen)
{
}

Camera::Camera(const Camera &other)
    : origin(other.origin), screen(other.screen)
{
}

Camera &Camera::operator=(const Camera &other)
{
    if (this != &other) {
        origin = other.origin;
        screen = other.screen;
    }
    return *this;
}

void Camera::rotateX(double degrees)
{
    screen.rotateXSelf(degrees);
}

void Camera::rotateY(double degrees)
{
    screen.rotateYSelf(degrees);
}

void Camera::rotateZ(double degrees)
{
    screen.rotateZSelf(degrees);
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

Math::Ray Camera::ray(double u, double v) const
{
    Math::Point3D point = screen.pointAt(u, v);

    Math::Vector3D direction(
        point._x - origin._x,
        point._y - origin._y,
        point._z - origin._z
    );

    return Math::Ray(origin, direction);
}
}
