//
// Created by tesniereliott on 5/6/25.
//

#include <unistd.h>

#include <iostream>

#include "LoaderType.hpp"
#include "Tanglecube.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Tanglecube *create(const Math::Point3D &position,
                                            const double &size
    )
    {
        return new RayTracer::primitive::Tanglecube(position, size);
    }
    RayTracer::Loader::ModuleType getType(void)
    {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Tanglecube" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Tanglecube" << std::endl;
#endif
    }
}
