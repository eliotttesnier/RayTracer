/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** MaterialFactory
*/

#include "MaterialFactory.hpp"
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace RayTracer::Factory {

std::shared_ptr<RayTracer::Materials::IMaterial> MaterialFactory::createMaterial(
    const Math::Vector3D &config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<RayTracer::Materials::IMaterial>> materialStack;

    materialStack.emplace_back(
        std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["DefaultMaterial"]->initEntryPointPtr<RayTracer::Materials::DefaultMaterial>(
                "create"
            )
        )
    );

    double transparency = config._x;
    if (transparency > 0.0) {
        materialStack.emplace_back(
            std::shared_ptr<RayTracer::Materials::IMaterial>(
                plugins["TransparencyMaterial"]->initEntryPointPtr<RayTracer::Materials::TransparencyMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1),
                    transparency
                )
            )
        );
    }

    double reflection = config._y;
    if (reflection > 0.0) {
        // materialStack.emplace_back(
        //     std::shared_ptr<RayTracer::Materials::IMaterial>(
        //         plugins["ReflectionMaterial"]->initEntryPointPtr<RayTracer::Materials::ReflectionMaterial>(
        //             "create",
        //             materialStack.at(materialStack.size() - 1),
        //             reflection
        //         )
        //     )
        // );
    }

    double refraction = config._z;
    if (refraction > 0.0) {
        // materialStack.emplace_back(
        //     std::shared_ptr<RayTracer::Materials::IMaterial>(
        //         plugins["RefractionMaterial"]->initEntryPointPtr<RayTracer::Materials::RefractionMaterial>(
        //             "create",
        //             materialStack.at(materialStack.size() - 1),
        //             refraction
        //         )
        //     )
        // );
    }

    return materialStack.at(materialStack.size() - 1);
}

}
