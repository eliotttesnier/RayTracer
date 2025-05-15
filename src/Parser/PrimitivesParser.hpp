//
// Created by roussierenoa on 5/12/25.
//

#ifndef PRIMITIVEPARSER_HPP
#define PRIMITIVEPARSER_HPP
#include <vector>
#include <libconfig.h++>
#include <iostream>
#include "ParserConfig/PrimitivesConfig.hpp"


namespace RayTracer {
namespace Parser {

class PrimitivesParser {
public:
    static std::vector<sphere_t> getSpheresData(const libconfig::Setting &root);
    static std::vector<plane_t> getPlanesData(const libconfig::Setting &root);
    static std::vector<cylinder_t> getCylindersData(const libconfig::Setting &root);
    static std::vector<cone_t> getConesData(const libconfig::Setting &root);
    static std::vector<torus_t> getTorusData(const libconfig::Setting &root);
    static std::vector<tanglecube_t> getTangleCubesData(const libconfig::Setting &root);
    static std::vector<triangle_t> getTrianglesData(const libconfig::Setting &root);
    static std::vector<obj_t> getOBJsData(const libconfig::Setting &root);
    static std::vector<infinitecylinder_t> getInfiniteCylindersData(const libconfig::Setting &root);
    static std::vector<infinitecone_t> getInfiniteConesData(const libconfig::Setting &root);
    static std::vector<fractalecube_t> getFractaleCubesData(const libconfig::Setting &root);
    static std::vector<mobius_t> getMobiusStripsData(const libconfig::Setting &root);
    PrimitivesParser() = delete;
    ~PrimitivesParser() = default;
};

} // Parser
} // RayTracer

#endif //PRIMITIVEPARSER_HPP
