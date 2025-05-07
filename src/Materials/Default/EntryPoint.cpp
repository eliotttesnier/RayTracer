/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** EntryPoint
*/

#include <iostream>
#include <unistd.h>
#include "LoaderType.hpp"
#include "DefaultMaterial.hpp"

extern "C" {
    RayTracer::Materials::DefaultMaterial *create() {
        return new RayTracer::Materials::DefaultMaterial();
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
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
