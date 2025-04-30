/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../Math/Point3D.hpp"
#include "../Math/Rectangle3D.hpp"
#include "../Math/Ray.hpp"

namespace RayTracer {
class Camera {
    public:
        Math::Point3D origin;
        RayTracer::Rectangle3D screen;

        Camera();
        Camera(const Math::Point3D &origin, const RayTracer::Rectangle3D &screen);
        Camera(const Camera &other);
        Camera &operator=(const Camera &other);
        ~Camera() = default;

        void rotateX(double degrees);
        void rotateY(double degrees);
        void rotateZ(double degrees);
        void tilt(double degrees);
        void pan(double degrees);
        void roll(double degrees);

        Math::Ray ray(double u, double v) const;
};
}

#endif /* !CAMERA_HPP_ */
