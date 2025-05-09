/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** MaterialFactory
*/

#include "MaterialFactory.hpp"

namespace RayTracer::Factory {

std::shared_ptr<RayTracer::Materials::IMaterial> MaterialFactory::createMaterial(
    const std::vector<std::string> &config,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::shared_ptr<RayTracer::Materials::IMaterial> material(
        plugins["DefaultMaterial"]->initEntryPointPtr<RayTracer::Materials::DefaultMaterial>(
            "create"
        )
    );

    for (const auto &mat : config) {
        // Add more material types here as needed with this pattern
        // (the objective is to have a recursion of materials):

        // if (mat == "...") {
        //     material = std::shared_ptr<RayTracer::Materials::...Material("create", config);
        // }
    }
    return material;
}

}
