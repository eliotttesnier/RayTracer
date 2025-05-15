/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** EntryPoint
*/

#include <unistd.h>
#include <iostream>

#include "LoaderType.hpp"
#include "Mobius.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Mobius *create(const Math::Point3D &position,
                                        const double &majorRadius,
                                        const double &minorRadius)
    {
        return new RayTracer::primitive::Mobius(position, majorRadius, minorRadius);
    }
    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Mobius" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Mobius" << std::endl;
#endif
    }
}