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
        std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> _sphere; // Position + raduis, Color
        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> _cylinders; // Position + raduis + height, Color
        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> _cone; // Position + raduis + height, Color
        std::vector<std::tuple<char, double, std::tuple<int, int, int>>> _plane; // axis, position, Color
    public:
        std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> getSpheres() const;

        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> getCylinders() const;

        std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> getCone() const;

        std::vector<std::tuple<char, double, std::tuple<int, int, int>>> getPlanes() const;


        PrimitivesConfig() = delete;
        PrimitivesConfig(const std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> &sphere,
                         const std::vector<std::tuple<char, double, std::tuple<int, int, int>>> &plane,
                         const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &cylinders,
                         const std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> &cone);
        ~PrimitivesConfig() = default;
    };

} // Parser
} // raytracer

#endif //PRIMITIVESCONFIG_HPP
