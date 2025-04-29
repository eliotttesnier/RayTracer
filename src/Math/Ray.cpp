/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-bsraytracer-eliott.tesnier
** File description:
** Ray
*/

#include "Ray.hpp"

namespace Math {
Ray::Ray() : origin(), direction()
{
}

Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
    : origin(origin), direction(direction)
{
}
}
