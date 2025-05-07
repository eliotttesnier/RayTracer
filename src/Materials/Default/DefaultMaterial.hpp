/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** DefaultMaterial
*/

#ifndef DEFAULTMATERIAL_HPP_
#define DEFAULTMATERIAL_HPP_

#include <cmath>

#include "../AMaterial.hpp"

namespace RayTracer::Materials {

class DefaultMaterial : public AMaterial {
    public:
        DefaultMaterial();
        ~DefaultMaterial() = default;
};

};

#endif /* !DEFAULTMATERIAL_HPP_ */
