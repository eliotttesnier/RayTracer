/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Math {
    class Ray {
        public:
            Math::Point3D origin;
            Math::Vector3D direction;

            Ray();
            Ray(const Math::Point3D &origin, const Math::Vector3D &direction);
            ~Ray() = default;
    };
}

#endif /* !RAY_HPP_ */
