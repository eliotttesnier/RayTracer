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
#include <any>

namespace RayTracer::Factory {

std::shared_ptr<RayTracer::Materials::IMaterial> MaterialFactory::createMaterial(
    const std::map<std::string, std::any> &materialProps,
    std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins
)
{
    std::vector<std::shared_ptr<RayTracer::Materials::IMaterial>> materialStack;
    bool hasChess = false;

    materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
        plugins["DefaultMaterial"]->initEntryPointPtr<RayTracer::Materials::DefaultMaterial>(
            "create"
        )
    ));

    auto chessIt = materialProps.find("chess");
    if (chessIt != materialProps.end() && std::any_cast<bool>(chessIt->second)) {
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["ChessPatternMaterial"]->
                initEntryPointPtr<RayTracer::Materials::ChessPatternMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1)
                )
        ));
        hasChess = true;
    }

    auto fileTextureIt = materialProps.find("fileTexture");
    if (fileTextureIt != materialProps.end() &&
        std::any_cast<std::string>(fileTextureIt->second) != "" && !hasChess) {
        std::string filePath = std::any_cast<std::string>(fileTextureIt->second);
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["FileTextureMaterial"]->
                initEntryPointPtr<RayTracer::Materials::FileTextureMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1),
                    filePath
                )
        ));
    }

    auto transparencyIt = materialProps.find("transparency");
    if (transparencyIt != materialProps.end() &&
        std::any_cast<double>(transparencyIt->second) > 0.0) {
        double transparency = std::any_cast<double>(transparencyIt->second);
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["TransparencyMaterial"]->
                initEntryPointPtr<RayTracer::Materials::TransparencyMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1),
                    transparency
                )
        ));
    }

    auto reflectionIt = materialProps.find("reflection");
    if (reflectionIt != materialProps.end() &&
        std::any_cast<double>(reflectionIt->second) > 0.0) {
        double reflection = std::any_cast<double>(reflectionIt->second);
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins["ReflectionMaterial"]->initEntryPointPtr<RayTracer::Materials::ReflectionMaterial>(
                "create",
                materialStack.at(materialStack.size() - 1),
                reflection
            )
        ));
    }

    auto refractionIt = materialProps.find("refraction");
    if (refractionIt != materialProps.end() &&
        std::any_cast<double>(refractionIt->second) > 0.0) {
        // double refraction = std::any_cast<double>(refractionIt->second);
        // materialStack.emplace_back(
        //     std::shared_ptr<RayTracer::Materials::IMaterial>(
        //         plugins["RefractionMaterial"]->initEntryPointPtr<RayTracer::Materials::RefractionMaterial>(
        //             "create",
        //             refraction
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
