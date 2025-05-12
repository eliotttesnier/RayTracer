/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** AMaterial
*/

#include "AMaterial.hpp"

#include <iostream>

namespace RayTracer::Materials {

AMaterial::~AMaterial() = default;

void AMaterial::setWrappee(std::shared_ptr<IMaterial> wrappee)
{
    _wrappee = wrappee;
}

}
