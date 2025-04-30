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

namespace raytracer::Parser {
    class Parser {
    private:
        std::unique_ptr<CameraConfig> _camConfig;
        std::unique_ptr<LightsConfig> _lightConfig;
        std::unique_ptr<PrimitivesConfig> _primitiveConfig;

        void _getCameraData(const libconfig::Setting &root);
        void _getPrimitivesData(const libconfig::Setting &root);
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
