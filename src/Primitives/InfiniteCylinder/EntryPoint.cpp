/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** EntryPoint
*/

#include <unistd.h>
#include <iostream>
#include "../../LibLoader/LoaderType.hpp"
#include "InfiniteCylinder.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::InfiniteCylinder *create(const Math::Point3D &position,
                                                  const double &radius)
    {
        return new RayTracer::primitive::InfiniteCylinder(position, radius);
    }

    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }

    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib InfiniteCylinder" << std::endl;
#endif
    }

    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib InfiniteCylinder" << std::endl;
#endif
    }
}
