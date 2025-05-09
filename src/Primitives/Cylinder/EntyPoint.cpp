//
// Created by roussierenoa on 5/2/25.
//

#include <unistd.h>

#include <iostream>

#include "LoaderType.hpp"
#include "Cylinder.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Cylinder *create(const Math::Point3D &position,
                                           const double &radius,
                                           const double &height)
    {
        return new RayTracer::primitive::Cylinder(position, radius, height);
    }
    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Cylinder" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Cylinder" << std::endl;
#endif
    }
}
