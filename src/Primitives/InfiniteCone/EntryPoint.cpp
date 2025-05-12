/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** EntryPoint
*/

#include <unistd.h>
#include <iostream>
#include "../../LibLoader/LoaderType.hpp"
#include "InfiniteCone.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::InfiniteCone *create(const Math::Point3D &position,
                                              const double &angle)
    {
        return new RayTracer::primitive::InfiniteCone(position, angle);
    }

    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }

    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib InfiniteCone" << std::endl;
#endif
    }

    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib InfiniteCone" << std::endl;
#endif
    }
}
