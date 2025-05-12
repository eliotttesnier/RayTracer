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
#include "TransparencyMaterial.hpp"

extern "C" {
    RayTracer::Materials::TransparencyMaterial *create(
        const std::shared_ptr<RayTracer::Materials::IMaterial> &wrappee,
        const double &transparency
    ) {
        return new RayTracer::Materials::TransparencyMaterial(wrappee, transparency);
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct() {
        #ifdef _DEBUG
                std::cout << "Loaded dynamic lib: Lib TransparencyMaterial" << std::endl;
        #endif
    }
    __attribute__((destructor)) void deconstruct() {
        #ifdef _DEBUG
                std::cout << "Unloaded dynamic lib: Lib TransparencyMaterial" << std::endl;
        #endif
    }
}
