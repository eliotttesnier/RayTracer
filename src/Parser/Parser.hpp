//
// Created by roussierenoa on 4/30/25.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <libconfig.h++>
#include <memory>
#include <vector>
#include <unordered_set>
#include <string>
#include "ParserConfig/LightsConfig.hpp"
#include "ParserConfig/CameraConfig.hpp"
#include "ParserConfig/PrimitivesConfig.hpp"

namespace RayTracer::Parser {

class Parser {
    private:
        template<typename T>
        static std::tuple<T, T, T> _getData3D(const libconfig::Setting &pos,
                                              const std::string &fst = "x",
                                              const std::string &snd = "y",
                                              const std::string &trd = "z") {
            return std::make_tuple(static_cast<T>(pos[fst]),
                                   static_cast<T>(pos[snd]),
                                   static_cast<T>(pos[trd]));
        }
        template<typename T>
        static std::tuple<T, T> _getData2D(const libconfig::Setting &pos, const std::string &fst = "x", const std::string &snd = "y") {
            return std::make_tuple(static_cast<T>(pos[fst]), static_cast<T>(pos[snd]));
        }
        std::unique_ptr<CameraConfig> _camConfig;
        std::unique_ptr<LightsConfig> _lightConfig;
        std::unique_ptr<PrimitivesConfig> _primitiveConfig;
        std::unordered_set<std::string> _importedScenes;

        void _getCameraData(const libconfig::Setting &root);
        void _getPrimitivesData(const libconfig::Setting &root);

        std::vector<sphere_t> _getSpheresData(const libconfig::Setting &root);
        std::vector<plane_t> _getPlanesData(const libconfig::Setting &root);
        std::vector<cylinder_t> _getCylindersData(const libconfig::Setting &root);
        std::vector<cone_t> _getConesData(const libconfig::Setting &root);
        std::vector<torus_t> _getTorusData(const libconfig::Setting &root);
        std::vector<tanglecube_t> _getTanglecubesData(const libconfig::Setting &root);
        std::vector<triangle_t> _getTrianglesData(const libconfig::Setting &root);
        std::vector<obj_t> _getOBJsData(const libconfig::Setting &root);
        std::vector<infinitecylinder_t> _getInfiniteCylindersData(const libconfig::Setting &root);
        std::vector<infinitecone_t> _getInfiniteConesData(const libconfig::Setting &root);
        std::vector<fractalecube_t> _getFractaleCubesData(const libconfig::Setting &root);

        void _importScenes(const libconfig::Setting &root);
        void _importScene(const std::string &filepath, libconfig::Setting &targetRoot);
        void _importPrimitives(const libconfig::Setting &sourceRoot, libconfig::Setting &targetRoot);
        void _importLights(const libconfig::Setting &sourceRoot, libconfig::Setting &targetRoot);
        void _copySettings(const libconfig::Setting &source, libconfig::Setting &target);

        ambient_t _getAmbientData(const libconfig::Setting &root);
        std::vector<directional_t> _getDirectionalData(const libconfig::Setting &root);

        void _getLightsData(const libconfig::Setting &root);

    public:
        CameraConfig getCameraConfig() const;
        LightsConfig getLightConfig() const;
        PrimitivesConfig getPrimitivesConfig() const;

        Parser() = delete;
        Parser(char *path);
        ~Parser() = default;
};

}

#endif //PARSER_HPP
