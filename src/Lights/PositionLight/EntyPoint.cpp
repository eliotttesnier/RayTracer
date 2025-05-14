//
// Created by roussierenoa on 5/2/25.
//

#include <unistd.h>

#include <iostream>

#include "LoaderType.hpp"
#include "PositionLight.hpp"
#include "../ILight.hpp"

extern "C" {
    RayTracer::light::PositionLight *create(void) {
        return new RayTracer::light::PositionLight();
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::LIGHT_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib PositionLight" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib PositionLight" << std::endl;
#endif
    }
}
