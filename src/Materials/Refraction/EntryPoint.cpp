/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** EntryPoint
*/

#include <unistd.h>

#include <iostream>
#include <memory>

#include "LoaderType.hpp"
#include "RefractionMaterial.hpp"

extern "C" {
    RayTracer::Materials::RefractionMaterial *create(
        const std::shared_ptr<RayTracer::Materials::IMaterial> &wrappee,
        const double &refraction
    ) {
        return new RayTracer::Materials::RefractionMaterial(wrappee, refraction);
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct() {
        #ifdef _DEBUG
                std::cout << "Loaded dynamic lib: Lib RefractionMaterial" << std::endl;
        #endif
    }
    __attribute__((destructor)) void deconstruct() {
        #ifdef _DEBUG
                std::cout << "Unloaded dynamic lib: Lib RefractionMaterial" << std::endl;
        #endif
    }
}
