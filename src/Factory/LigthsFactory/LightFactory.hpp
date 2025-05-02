//
// Created by roussierenoa on 5/1/25.
//

#ifndef LIGHTFACTORY_HPP
#define LIGHTFACTORY_HPP
#include <vector>
#include <memory>
#include "Parser/ParserConfig/LightsConfig.hpp"
#include "ILightFactory.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace raytracer::Factory {

class LightFactory {
public:
    static std::vector<std::unique_ptr<ILight>> createLights(const raytracer::Parser::LightsConfig &config);
    LightFactory() = default;
    ~LightFactory() = delete;
};
} // raytracer

#endif //LIGHTFACTORY_HPP
