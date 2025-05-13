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
#include "FileTextureMaterial.hpp"

extern "C" {
    RayTracer::Materials::FileTextureMaterial *create(
        const std::shared_ptr<RayTracer::Materials::IMaterial> &wrappee,
        const std::string &filePath)
    {
        return new RayTracer::Materials::FileTextureMaterial(wrappee, filePath);
    }

    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib FileTextureMaterial" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib FileTextureMaterial" << std::endl;
#endif
    }
}
