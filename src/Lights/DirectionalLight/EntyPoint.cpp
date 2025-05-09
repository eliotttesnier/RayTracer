//
// Created by roussierenoa on 5/2/25.
//

#include <unistd.h>

#include <iostream>

#include "LoaderType.hpp"
#include "DirectionalLight.hpp"
#include "../ILight.hpp"

extern "C" {
    RayTracer::light::DirectionalLight *create(void) {
        return new RayTracer::light::DirectionalLight();
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::LIGHT_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib DirectionalLight" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib DirectionalLight" << std::endl;
#endif
    }
}
