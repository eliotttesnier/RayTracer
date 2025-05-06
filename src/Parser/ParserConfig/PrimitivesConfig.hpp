//
// Created by roussierenoa on 4/30/25.
//

#ifndef PRIMITIVESCONFIG_HPP
#define PRIMITIVESCONFIG_HPP
#include <vector>
#include <memory>

namespace RayTracer {
namespace Parser {

    class PrimitivesConfig {
        std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> _sphere; // Position + radius, Color
        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> _cylinders; // Position + radius + height, Color
        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> _cone; // Position + radius + height, Color
        std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> _plane; // axis, position, Color
        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> _torus; // Position + major radius + minor radius, Color
    public:
        std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> getSpheres() const;

        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> getCylinders() const;

        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> getCone() const;

        std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> getPlanes() const;

        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> getTorus() const;

        PrimitivesConfig() = delete;
        PrimitivesConfig(const std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> &sphere,
                         const std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> &plane,
                         const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &cylinders,
                         const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &cone,
                         const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &torus);
        ~PrimitivesConfig() = default;
    };

} // Parser
} // raytracer

#endif //PRIMITIVESCONFIG_HPP
