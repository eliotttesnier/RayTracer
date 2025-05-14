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
#include "PrimitivesParser.hpp"
#include "LightsParser.hpp"
#include "ParserConfig/LightsConfig.hpp"
#include "ParserConfig/CameraConfig.hpp"
#include "ParserConfig/PrimitivesConfig.hpp"
#include "ParserConfig/AntialiasingConfig.hpp"

namespace RayTracer::Parser {

class Parser {
    private:
        std::unique_ptr<CameraConfig> _camConfig;
        std::unique_ptr<LightsConfig> _lightConfig;
        std::unordered_set<std::string> _importedScenes;
        std::unique_ptr<PrimitivesConfig> _primitiveConfig;
        std::unique_ptr<AntialiasingConfig> _antialiasingConfig;

        void _getCameraData(const libconfig::Setting &root);
        void _getPrimitivesData(const libconfig::Setting &root);
        void _getLightsData(const libconfig::Setting &root);
        void _getAntialiasingData(const libconfig::Setting &root);

        void _importScenes(const libconfig::Setting &root);
        void _importScene(const std::string &filepath, libconfig::Setting &targetRoot);
        void _importPrimitives(const libconfig::Setting &sourceRoot, libconfig::Setting &targetRoot);
        void _importLights(const libconfig::Setting &sourceRoot, libconfig::Setting &targetRoot);
        void _copySettings(const libconfig::Setting &source, libconfig::Setting &target);


    public:
        template<typename T>
        static std::tuple<T, T, T> getData3D(const libconfig::Setting &pos,
            const std::string &fst = "x",
            const std::string &snd = "y",
            const std::string &trd = "z") {
            return std::make_tuple(static_cast<T>(pos[fst.c_str()]),
                static_cast<T>(pos[snd.c_str()]),
                static_cast<T>(pos[trd.c_str()]));
        }
        template<typename T>
        static std::tuple<T, T> getData2D(const libconfig::Setting &pos, const std::string &fst = "x", const std::string &snd = "y") {
            return std::make_tuple(static_cast<T>(pos[fst.c_str()]), static_cast<T>(pos[snd.c_str()]));
        }

        static material_t getMaterialData(const libconfig::Setting &setting);

        CameraConfig getCameraConfig() const;
        LightsConfig getLightConfig() const;
        PrimitivesConfig getPrimitivesConfig() const;
        AntialiasingConfig getAntialiasingConfig() const;

        Parser() = delete;
        Parser(char *path);
        ~Parser() = default;
};

}

#endif //PARSER_HPP
