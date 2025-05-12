//
// Created by roussierenoa on 4/30/25.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <libconfig.h++>
#include <memory>
#include <vector>
#include "ParserConfig/LightsConfig.hpp"
#include "ParserConfig/CameraConfig.hpp"
#include "ParserConfig/PrimitivesConfig.hpp"

namespace RayTracer::Parser {

    using fractalecube_t = std::tuple<
        std::tuple<double, double, double, double>, // position + size
        std::tuple<double, double, double>,         // rotation
        std::tuple<double, double, double>,         // scale
        std::tuple<int, int, int>                   // color
    >;


class Parser {
    private:
        std::unique_ptr<CameraConfig> _camConfig;
        std::unique_ptr<LightsConfig> _lightConfig;
        std::unique_ptr<PrimitivesConfig> _primitiveConfig;

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
        std::vector<fractalecube_t> _getFractaleCubesData(const libconfig::Setting &root);

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
