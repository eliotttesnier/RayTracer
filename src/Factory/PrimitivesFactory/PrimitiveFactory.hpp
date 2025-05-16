//
// Created by roussierenoa on 5/1/25.
//

#ifndef PRIMITIVEFACTORY_HPP
#define PRIMITIVEFACTORY_HPP
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <string>
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
#include "RectangleFactory.hpp"
#include "../MaterialFactory/MaterialFactory.hpp"
#include "InfiniteConeFactory.hpp"
#include "InfiniteCylinderFactory.hpp"
#include "../../Primitives/InfiniteCone/InfiniteCone.hpp"
#include "../../Primitives/InfiniteCylinder/InfiniteCylinder.hpp"

namespace RayTracer::Factory {

class PrimitiveFactory {
    public:
        static std::vector<std::shared_ptr<IPrimitive>> createPrimitives(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        PrimitiveFactory() = default;
        ~PrimitiveFactory() = delete;
    private:
        static std::vector<std::shared_ptr<IPrimitive>> _addSpheres(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addPlanes(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addCylinders(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addCones(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addToruses(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addTanglecubes(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addTriangles(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addOBJs(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addInfiniteCones(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addInfiniteCylinders(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        static std::vector<std::shared_ptr<IPrimitive>> _addRectangles(
            const RayTracer::Parser::PrimitivesConfig &config,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
};
} // raytracer

#endif //PRIMITIVEFACTORY_HPP
