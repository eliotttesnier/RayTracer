//
// Created by roussierenoa on 5/1/25.
//

#ifndef LIGHTFACTORY_HPP
#define LIGHTFACTORY_HPP
#include <vector>
#include <memory>
#include <map>
#include "LibLoader/LibLoader.hpp"
#include "Parser/ParserConfig/LightsConfig.hpp"
#include "ILightFactory.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer::Factory {

class LightFactory {
public:
    static std::vector<std::shared_ptr<ILight>> createLights(
        const RayTracer::Parser::LightsConfig &config,
        const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
    );
    LightFactory() = default;
    ~LightFactory() = delete;
};
} // raytracer

#endif //LIGHTFACTORY_HPP
