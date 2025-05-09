/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <tuple>
#include "../Math/Point3D.hpp"
#include "../Math/Rectangle3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Matrix4x4.hpp"

namespace RayTracer {
class Camera {
    public:
        Math::Point3D origin;
        RayTracer::Rectangle3D screen;
        std::tuple<int, int> resolution;
        double fov;
        Math::Matrix4x4 transformMatrix;

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
        void setPosition(double x, double y, double z);
        Math::Point3D getPosition() const;
        void setRotation(double x, double y, double z);
        void updateTransformMatrix();
        std::tuple<int, int> getResolution() const;
        double getFov() const;

        Math::Ray ray(double u, double v) const;
};
}

#endif /* !CAMERA_HPP_ */
