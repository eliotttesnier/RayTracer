/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** EntryPoint
*/

#include <iostream>
#include "LoaderType.hpp"
#include "Triangles.hpp"
#include "../IPrimitive.hpp"

extern "C" {
    RayTracer::primitive::Triangles *create(const Math::Point3D &p1,
                                          const Math::Point3D &p2,
                                          const Math::Point3D &p3) {
        return new RayTracer::primitive::Triangles(p1, p2, p3);
    }

    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }

    __attribute__((constructor))
    void construct() {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib Triangles" << std::endl;
#endif
    }

    __attribute__((destructor))
    void deconstruct() {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib Triangles" << std::endl;
#endif
    }
}
