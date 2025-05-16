/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** MaterialFactory
*/

#ifndef MATERIALFACTORY_HPP_
#define MATERIALFACTORY_HPP_

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <any>

#include "../../Materials/IMaterial.hpp"
#include "../../Materials/Default/DefaultMaterial.hpp"
#include "../../Materials/Transparency/TransparencyMaterial.hpp"
#include "../../Materials/Reflection/ReflectionMaterial.hpp"
#include "../../Materials/Refraction/RefractionMaterial.hpp"
#include "../../Materials/ChessPattern/ChessPatternMaterial.hpp"
#include "../../Materials/FileTexture/FileTextureMaterial.hpp"
#include "../../Materials/PerlinNoise/PerlinNoiseMaterial.hpp"
#include "../../Materials/NormalMapping/NormalMappingMaterial.hpp"
#include "../../LibLoader/LibLoader.hpp"
#include "../../Math/Vector3D.hpp"

namespace RayTracer::Factory {

typedef std::tuple<double, double, double, double> phong_t;
typedef std::tuple<int, double> ambientOcclusion_t;
typedef std::tuple<phong_t, ambientOcclusion_t> shading_t; // Shading properties

class MaterialFactory {
    public:
        static std::shared_ptr<RayTracer::Materials::IMaterial> createMaterial(
            const std::map<std::string, std::any> &materialProps,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins,
            shading_t shading
        );
        MaterialFactory() = default;
        ~MaterialFactory() = delete;
};

}

#endif /* !MATERIALFACTORY_HPP_ */
