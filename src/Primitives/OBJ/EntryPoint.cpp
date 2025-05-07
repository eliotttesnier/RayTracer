/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** EntryPoint
*/

#include <unistd.h>

#include <iostream>
#include <string>

#include "LoaderType.hpp"
#include "OBJ.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::OBJ *create(const Math::Point3D &position,
                                      const std::string &filepath)
    {
        return new RayTracer::primitive::OBJ(position, filepath);
    }

    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }

    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib OBJ" << std::endl;
#endif
    }

    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib OBJ" << std::endl;
#endif
    }
}
