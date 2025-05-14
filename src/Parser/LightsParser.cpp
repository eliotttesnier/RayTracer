//
// Created by roussierenoa on 5/12/25.
//

#include <vector>
#include <iostream>
#include "LightsParser.hpp"
#include "Parser.hpp"

RayTracer::Parser::ambient_t
    RayTracer::Parser::LightsParser::getAmbientData(const libconfig::Setting &root)
{
    ambient_t ambientData;

    try {
        const auto &s = root["lights"]["ambient"];
        auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
        double intensity = s["intensity"];
        ambientData = std::make_tuple(intensity, color);
        #ifdef _DEBUG
            std::cout << "Ambient Light: intensity= "<< intensity
                      << ", color(" << std::get<0>(color) << ", " <<  std::get<1>(color) <<
                          ", " << std::get<2>(color) << ")" << std::endl;
        #endif
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[WARNING] Ambient light not found in config" << std::endl;
        ambientData = std::make_tuple(0.0, std::make_tuple(0, 0, 0));
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Ambient light setting type error: " << e.what() << std::endl;
        ambientData = std::make_tuple(0.0, std::make_tuple(0, 0, 0));
    }
    return ambientData;
}

std::vector<RayTracer::Parser::directional_t>
    RayTracer::Parser::LightsParser::getDirectionalData(const libconfig::Setting &root)
{
    std::vector<RayTracer::Parser::directional_t> directionalData;
    try {
        const auto &directional = root["lights"]["directional"];

        for (int i = 0; i < directional.getLength(); ++i) {
            const auto &s = directional[i];
            auto direction = RayTracer::Parser::Parser::getData3D<double>(s["direction"]);
            auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
            double intensity = s["intensity"];
            directionalData.emplace_back(
                intensity,
                position,
                direction,
                color
            );
#ifdef _DEBUG
            std::cout << "Directional Light " << i << ": intensity= " << intensity
                    << ", direction(" << std::get<0>(direction) << ", " <<
                    std::get<1>(direction) << ", " << std::get<2>(direction) << ")"
                    << ", position(" << std::get<0>(position) << ", " <<
                    std::get<1>(position) << ", " << std::get<2>(position) << ")"
                    << ", color(" << std::get<0>(color) << ", " <<
                    std::get<1>(color) << ", " << std::get<2>(color) << ")" << std::endl;
#endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
#ifdef _DEBUG
        std::cout << "No Directional light found in config" << std::endl;
#endif
    }
    return directionalData;
}

std::vector<RayTracer::Parser::point_t> RayTracer::Parser::LightsParser::getPositionData(
    const libconfig::Setting &root)
{
    std::vector<RayTracer::Parser::point_t> positionData;
    try {
        const auto &positionRoot = root["lights"]["point"];
        for (int i = 0; i < positionRoot.getLength(); ++i) {
            const auto &s = positionRoot[i];
            auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
            double intensity = s["intensity"];
            positionData.emplace_back(
                intensity,
                position,
                color
            );
#ifdef _DEBUG
            std::cout << "Point Light " << i << ": intensity= " << intensity
                    << ", position(" << std::get<0>(position) << ", " <<
                    std::get<1>(position) << ", " << std::get<2>(position) << ")"
                    << ", color(" << std::get<0>(color) << ", " <<
                    std::get<1>(color) << ", " << std::get<2>(color) << ")" << std::endl;
#endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
#ifdef _DEBUG
        std::cout << "No Point light found in config" << std::endl;
#endif
    }
    return positionData;
}
