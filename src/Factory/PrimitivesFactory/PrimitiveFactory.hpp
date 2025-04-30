//
// Created by roussierenoa on 5/1/25.
//

#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <vector>
#include <memory>
#include "../../Parser/ParserConfig/PrimitivesConfig.hpp"
#include "IPrimitiveFactory.hpp"
#include "PlaneFactory.hpp"
#include "SphereFactory.hpp"
#include "../../Math/Point3D.hpp"
#include "../../Math/Vector3D.hpp"

namespace raytracer::Factory {

class PrimitiveFactory {
public:
    static std::vector<std::unique_ptr<IPrimitive>> createPrimitives(const raytracer::Parser::PrimitivesConfig& config);
};
} // raytracer

#endif //FACTORY_HPP
