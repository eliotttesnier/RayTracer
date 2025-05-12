//
// Created by roussierenoa on 5/2/25.
//

#include <unistd.h>

#include <iostream>
#include <tuple>

#include "LoaderType.hpp"
#include "Plane.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Plane *create(const Math::Point3D &position,
                                        const Math::Vector3D &rotation)
    {
        return new RayTracer::primitive::Plane(position, rotation);
    }
    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Plane" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Plane" << std::endl;
#endif
    }
}
