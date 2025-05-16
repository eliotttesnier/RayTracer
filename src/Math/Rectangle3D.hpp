/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP_
#define RECTANGLE3D_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"

namespace RayTracer {
class Rectangle3D {
    public:
        Math::Point3D origin;
        Math::Vector3D bottom_side;
        Math::Vector3D left_side;

        Rectangle3D();
        Rectangle3D(const Math::Point3D &origin,
                    const Math::Vector3D &bottom_side,
                    const Math::Vector3D &left_side);
        ~Rectangle3D() = default;

        Math::Point3D pointAt(double u, double v) const;

        Math::Vector3D getNormal() const;

        Rectangle3D translate(const Math::Vector3D &translation) const;
        Rectangle3D &translateSelf(const Math::Vector3D &translation);

        Rectangle3D rotateX(double degrees) const;
        Rectangle3D &rotateXSelf(double degrees);

        Rectangle3D rotateY(double degrees) const;
        Rectangle3D &rotateYSelf(double degrees);

        Rectangle3D rotateZ(double degrees) const;
        Rectangle3D &rotateZSelf(double degrees);
};
}

#endif /* !RECTANGLE3D_HPP_ */
