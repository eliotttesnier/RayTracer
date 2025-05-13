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
#include <iostream>

namespace RayTracer::Factory {

std::shared_ptr<RayTracer::Materials::IMaterial> MaterialFactory::createMaterial(
    const std::map<std::string, double> &materialProps,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<RayTracer::Materials::IMaterial>> materialStack;

    materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
        plugins["DefaultMaterial"]->initEntryPointPtr<RayTracer::Materials::DefaultMaterial>(
            "create"
        )
    ));

    auto chessIt = materialProps.find("chess");
    if (chessIt != materialProps.end() && chessIt->second > 0.0) {
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["ChessPatternMaterial"]->
                initEntryPointPtr<RayTracer::Materials::ChessPatternMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1)
                )
        ));
    }

    auto transparencyIt = materialProps.find("transparency");
    if (transparencyIt != materialProps.end() && transparencyIt->second > 0.0) {
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["TransparencyMaterial"]->
                initEntryPointPtr<RayTracer::Materials::TransparencyMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1),
                    transparencyIt->second
                )
        ));
    }

    auto reflectionIt = materialProps.find("reflection");
    if (reflectionIt != materialProps.end() && reflectionIt->second > 0.0) {
        // materialStack.emplace_back(
        //     std::shared_ptr<RayTracer::Materials::IMaterial>(
        //         plugins["ReflectionMaterial"]->initEntryPointPtr<RayTracer::Materials::ReflectionMaterial>(
        //             "create",
        //             reflectionIt->second
        //         )
        //     )
        // );
        // materialStack.at(materialStack.size() - 1)->setWrappee(
        //     materialStack.at(materialStack.size() - 2)
        // );
    }

    auto refractionIt = materialProps.find("refraction");
    if (refractionIt != materialProps.end() && refractionIt->second > 0.0) {
        // materialStack.emplace_back(
        //     std::shared_ptr<RayTracer::Materials::IMaterial>(
        //         plugins["RefractionMaterial"]->initEntryPointPtr<RayTracer::Materials::RefractionMaterial>(
        //             "create",
        //             refractionIt->second
        //         )
        //     )
        // );
        // materialStack.at(materialStack.size() - 1)->setWrappee(
        //     materialStack.at(materialStack.size() - 2)
        // );
    }

    return materialStack.at(materialStack.size() - 1);
}

}
