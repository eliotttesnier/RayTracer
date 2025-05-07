//
// Created by roussierenoa on 4/30/25.
//

#ifndef PRIMITIVESCONFIG_HPP
#define PRIMITIVESCONFIG_HPP
#include <vector>
#include <memory>
#include <string>

namespace RayTracer {
namespace Parser {

    class PrimitivesConfig {
        std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> _sphere; // Position + radius, Color
        std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> _cylinders; // Position + radius + height, Color
        std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> _cone; // Position + radius + height, Color
        std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> _plane; // axis, position, Color
        std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> _torus; // Position + major radius + minor radius, Color
        std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> _tanglecube; // Position + size, Color
        std::vector<std::tuple<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>>, std::tuple<double, double, double>, std::tuple<int, int, int>>> _triangles; // Three points (p1, p2, p3), Color
        std::vector<std::tuple<std::tuple<double, double, double, std::string>, std::tuple<double, double, double>, std::tuple<int, int, int>>> _obj; // Position + filepath, Color
    public:
        std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> getSpheres() const;

        std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getCylinders() const;

        std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getCone() const;

        std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> getPlanes() const;

        std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getTorus() const;

        std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getTanglecube() const;

        std::vector<std::tuple<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getTriangles() const;

        std::vector<std::tuple<std::tuple<double, double, double, std::string>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getOBJ() const;

        PrimitivesConfig() = delete;
        PrimitivesConfig(const std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> &sphere,
                         const std::vector<std::tuple<char, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double>, std::tuple<int, int, int>>> &plane,
                         const std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &cylinders,
                         const std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &cone,
                         const std::vector<std::tuple<std::tuple<double, double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &torus,
                         const std::vector<std::tuple<std::tuple<double, double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &tanglecube,
                         const std::vector<std::tuple<std::tuple<std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<double, double, double>>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &triangles,
                         const std::vector<std::tuple<std::tuple<double, double, double, std::string>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &obj);

        ~PrimitivesConfig() = default;
    };

} // Parser
} // raytracer

#endif //PRIMITIVESCONFIG_HPP
