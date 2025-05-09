//
// Created by tesniereliott on 5/6/25.
//

#include <unistd.h>

#include <iostream>

#include "LoaderType.hpp"
#include "Torus.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Torus *create(const Math::Point3D &position,
                                        const double &majorRadius,
                                        const double &minorRadius)
    {
        return new RayTracer::primitive::Torus(position, majorRadius, minorRadius);
    }
    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Torus" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Torus" << std::endl;
#endif
    }
}
