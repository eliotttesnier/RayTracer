/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** EntryPoint
*/

#include <unistd.h>
#include <iostream>
#include <memory>

#include "LoaderType.hpp"
#include "ChessPatternMaterial.hpp"

extern "C" {
    RayTracer::Materials::ChessPatternMaterial *create(
        const std::shared_ptr<RayTracer::Materials::IMaterial> &wrappee)
    {
        return new RayTracer::Materials::ChessPatternMaterial(wrappee);
    }

    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::MATERIAL_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib ChessPatternMaterial" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib ChessPatternMaterial" << std::endl;
#endif
    }
}
