/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** EntryPoint
*/

#include <unistd.h>
#include <iostream>
#include <memory>
#include <string>

#include "LoaderType.hpp"
#include "NormalMappingMaterial.hpp"

extern "C" {
    RayTracer::Materials::NormalMappingMaterial *create(
        const std::shared_ptr<RayTracer::Materials::IMaterial> &wrappee,
        const std::string &normalMapPath)
    {
        return new RayTracer::Materials::NormalMappingMaterial(wrappee, normalMapPath);
    }

    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib NormalMappingMaterial" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib NormalMappingMaterial" << std::endl;
#endif
    }
}
