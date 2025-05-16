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
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins,
    shading_t shading
)
{
    std::vector<std::shared_ptr<RayTracer::Materials::IMaterial>> materialStack;
    bool differentColor = false;

    materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
        plugins.at(
            "DefaultMaterial"
        )->initEntryPointPtr<RayTracer::Materials::DefaultMaterial>(
            "create",
            shading
        )
    ));

    auto chessIt = materialProps.find("chess");
    if (chessIt != materialProps.end() && std::any_cast<bool>(chessIt->second)) {
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins.at("ChessPatternMaterial")->
                initEntryPointPtr<RayTracer::Materials::ChessPatternMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1)
                )
        ));
        differentColor = true;
    }

    auto fileTextureIt = materialProps.find("fileTexture");
    if (fileTextureIt != materialProps.end() &&
        std::any_cast<std::string>(fileTextureIt->second) != "" && !differentColor) {
        std::string filePath = std::any_cast<std::string>(fileTextureIt->second);
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins.at("FileTextureMaterial")->
                initEntryPointPtr<RayTracer::Materials::FileTextureMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1),
                    filePath
                )
        ));
        differentColor = true;
    }

    auto perlinNoiseIt = materialProps.find("perlinNoise");
    if (
        perlinNoiseIt != materialProps.end() &&
        std::any_cast<bool>(perlinNoiseIt->second)
    ) {
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins.at("PerlinNoiseMaterial")->
                initEntryPointPtr<RayTracer::Materials::PerlinNoiseMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1)
                )
        ));
        differentColor = true;
    }

    auto normalMapIt = materialProps.find("normalMap");
    if (normalMapIt != materialProps.end() &&
    std::any_cast<std::string>(normalMapIt->second) != "") {
        std::string mapPath = std::any_cast<std::string>(normalMapIt->second);
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins.at("NormalMappingMaterial")->
            initEntryPointPtr<RayTracer::Materials::NormalMappingMaterial>(
                "create",
                materialStack.at(materialStack.size() - 1),
                mapPath
            )
        ));
    }

    auto transparencyIt = materialProps.find("transparency");
    if (transparencyIt != materialProps.end() &&
        std::any_cast<double>(transparencyIt->second) > 0.0) {
        double transparency = std::any_cast<double>(transparencyIt->second);
        materialStack.emplace_back(std::shared_ptr<RayTracer::Materials::IMaterial>(
            plugins.at("TransparencyMaterial")->
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
            plugins.at("ReflectionMaterial")->
                initEntryPointPtr<RayTracer::Materials::ReflectionMaterial>(
                "create",
                materialStack.at(materialStack.size() - 1),
                reflection
            )
        ));
    }

    auto refractionIt = materialProps.find("refraction");
    if (refractionIt != materialProps.end() &&
        std::any_cast<double>(refractionIt->second) > 0.0) {
        double refraction = std::any_cast<double>(refractionIt->second);
        materialStack.emplace_back(
            std::shared_ptr<RayTracer::Materials::IMaterial>(
                plugins.at("RefractionMaterial")->initEntryPointPtr<
                    RayTracer::Materials::RefractionMaterial>(
                    "create",
                    materialStack.at(materialStack.size() - 1),
                    refraction
                )
            )
        );
    }

    return materialStack.at(materialStack.size() - 1);
}

}
