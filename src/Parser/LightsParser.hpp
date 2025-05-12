//
// Created by roussierenoa on 5/12/25.
//

#ifndef LIGHTSPARSER_HPP
#define LIGHTSPARSER_HPP

#include <vector>
#include <iostream>
#include <libconfig.h++>
#include "ParserConfig/LightsConfig.hpp"

namespace RayTracer::Parser {
    class LightsParser {
    public:
        static ambient_t getAmbientData(const libconfig::Setting &root);
        static std::vector<directional_t> getDirectionalData(const libconfig::Setting &root);
        LightsParser() = delete;
        ~LightsParser() = default;
    };
}



#endif //LIGHTSPARSER_HPP
