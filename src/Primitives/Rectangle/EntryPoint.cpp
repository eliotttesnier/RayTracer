/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** EntryPoint
*/

#include <unistd.h>
#include <iostream>
#include "../../LibLoader/LoaderType.hpp"
#include "Rectangle.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Rectangle *create(
        const Math::Point3D &position,
        const double &length,
        const double &width,
        const double &height
    )
    {
        return new RayTracer::primitive::Rectangle(position, length, width, height);
    }

    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }

    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Rectangle" << std::endl;
#endif
    }

    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Rectangle" << std::endl;
#endif
    }
}
