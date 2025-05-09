//
// Created by roussierenoa on 5/1/25.
//

#ifndef PRIMITIVEFACTORY_HPP
#define PRIMITIVEFACTORY_HPP
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "LibLoader/LibLoader.hpp"
#include "Parser/ParserConfig/PrimitivesConfig.hpp"
#include "IPrimitiveFactory.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "PlaneFactory.hpp"
#include "SphereFactory.hpp"
#include "CylinderFactory.hpp"
#include "ConeFactory.hpp"
#include "TorusFactory.hpp"
#include "TanglecubeFactory.hpp"
#include "TrianglesFactory.hpp"
#include "OBJFactory.hpp"
#include "../MaterialFactory/MaterialFactory.hpp"

namespace RayTracer::Factory {

class PrimitiveFactory {
    public:
        static std::vector<std::shared_ptr<IPrimitive>> createPrimitives(
            const RayTracer::Parser::PrimitivesConfig& config,
            std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
        );
        PrimitiveFactory() = default;
        ~PrimitiveFactory() = delete;
    private:
        static std::vector<std::shared_ptr<IPrimitive>> _addSpheres(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addPlanes(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addCylinders(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addCones(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addToruses(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addTanglecubes(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addTriangles(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
        static std::vector<std::shared_ptr<IPrimitive>> _addOBJs(const RayTracer::Parser::PrimitivesConfig& config, std::map<std::string, std::unique_ptr<Loader::LibLoader>>& plugins);
};
} // raytracer

#endif //PRIMITIVEFACTORY_HPP
