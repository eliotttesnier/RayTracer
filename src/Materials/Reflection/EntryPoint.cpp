/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** Entrypoint
*/

#include <unistd.h>

#include <iostream>
#include <memory>

#include "LoaderType.hpp"
#include "ReflectionMaterial.hpp"

extern "C" {
    RayTracer::Materials::ReflectionMaterial *create(
        const std::shared_ptr<RayTracer::Materials::IMaterial> &wrappee,
        const double &reflection
    ) {
        return new RayTracer::Materials::ReflectionMaterial(wrappee, reflection);
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct() {
        #ifdef _DEBUG
                std::cout << "Loaded dynamic lib: Lib ReflectionMaterial" << std::endl;
        #endif
    }
    __attribute__((destructor)) void deconstruct() {
        #ifdef _DEBUG
                std::cout << "Unloaded dynamic lib: Lib ReflectionMaterial" << std::endl;
        #endif
    }
}
