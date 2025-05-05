//
// Created by roussierenoa on 5/1/25.
//

#ifndef PRIMITIVEFACTORY_HPP
#define PRIMITIVEFACTORY_HPP
#include <vector>
#include <memory>
#include <map>
#include "LibLoader/LibLoader.hpp"
#include "Parser/ParserConfig/PrimitivesConfig.hpp"
#include "IPrimitiveFactory.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer::Factory {

class PrimitiveFactory {
public:
    static std::vector<std::unique_ptr<IPrimitive>> createPrimitives(const RayTracer::Parser::PrimitivesConfig& config,
                                                                    std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins);
    PrimitiveFactory() = default;
    ~PrimitiveFactory() = delete;
};
} // raytracer

#endif //PRIMITIVEFACTORY_HPP
