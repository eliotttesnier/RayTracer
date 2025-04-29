/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** HitData
*/

#ifndef HITDATA_HPP_
#define HITDATA_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "../Graphic/Color.hpp"

namespace Math {
    typedef struct hitdata_s {
        bool hit;
        double distance;
        Point3D point;
        Vector3D normal;
        Graphic::color_t color;
    } hitdata_t;
}

#endif /* !HITDATA_HPP_ */
