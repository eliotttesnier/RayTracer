//
// Created by roussierenoa on 5/1/25.
//

#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <vector>

#include "../Parser/ParserConfig/CameraConfig.hpp"
#include "../Parser/ParserConfig/PrimitivesConfig.hpp"
#include "../Parser/ParserConfig/LightsConfig.hpp"
#include "../Primitives/IPrimitive.hpp"

namespace raytracer {
namespace Factory {

class Factory {
private:
public:
    std::tuple<std::vector<std::unique_ptr<IPrimitive>>> createElement(Parser::CameraConfig &cam,
                                                      Parser::PrimitivesConfig &scene,
                                                      Parser::LightsConfig &light);
    Factory() = default;
    ~Factory() = default;
};

} // Factory
} // raytracer

#endif //FACTORY_HPP
