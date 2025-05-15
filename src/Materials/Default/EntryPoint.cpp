/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** EntryPoint
*/

#include <unistd.h>

#include <iostream>

#include "LoaderType.hpp"
#include "DefaultMaterial.hpp"

extern "C" {
    RayTracer::Materials::DefaultMaterial *create(
        const RayTracer::Materials::shading_t &shading
    ) {
        return new RayTracer::Materials::DefaultMaterial(
            shading
        );
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
        #ifdef _DEBUG
                std::cout << "Loaded dynamic lib: Lib DefaultMaterial" << std::endl;
        #endif
    }
    __attribute__((destructor)) void deconstruct()
    {
        #ifdef _DEBUG
                std::cout << "Unloaded dynamic lib: Lib DefaultMaterial" << std::endl;
        #endif
    }
}
