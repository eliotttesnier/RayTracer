//
// Created by roussierenoa on 4/30/25.
//

#ifndef PRIMITIVESCONFIG_HPP
#define PRIMITIVESCONFIG_HPP

#include <vector>
#include <memory>
#include <string>
#include <tuple>

namespace RayTracer {
namespace Parser {

typedef std::tuple<double, double, double> truple_t;
typedef std::tuple<double, double, double, double> quaduple_t;
typedef std::tuple<double, double, double, double, double> quintuple_t;

typedef std::tuple<quaduple_t, truple_t, std::tuple<int, int, int>> sphere_t; // Position + radius, Color
typedef std::tuple<quintuple_t, truple_t, truple_t, std::tuple<int, int, int>> cylinder_t; // Position + radius + height, Color
typedef std::tuple<quintuple_t, truple_t, truple_t, std::tuple<int, int, int>> cone_t; // Position + radius + height, Color
typedef std::tuple<char, truple_t, truple_t, truple_t, std::tuple<double, double>, std::tuple<int, int, int>> plane_t; // axis, position, Color
typedef std::tuple<quintuple_t, truple_t, truple_t, std::tuple<int, int, int>> torus_t; // Position + major radius + minor radius, Color
typedef std::tuple<quaduple_t, truple_t, truple_t, std::tuple<int, int, int>> tanglecube_t; // Position + size, Color
typedef std::tuple<std::tuple<truple_t, truple_t, truple_t>, truple_t, truple_t, std::tuple<int, int, int>> triangle_t; // Three points (p1, p2, p3), Color
typedef std::tuple<std::tuple<double, double, double, std::string>, truple_t, truple_t, std::tuple<int, int, int>> obj_t; // Position + filepath, Color

class PrimitivesConfig {
    private:
        std::vector<sphere_t> _spheres;
        std::vector<cylinder_t> cylinders;
        std::vector<cone_t> _cones;
        std::vector<plane_t> planes;
        std::vector<torus_t> _toruses;
        std::vector<tanglecube_t> _tanglecubes;
        std::vector<triangle_t> _triangles;
        std::vector<obj_t> _objs;

    public:
        std::vector<sphere_t> getSpheres() const;
        std::vector<cylinder_t> getCylinders() const;
        std::vector<cone_t> getCone() const;
        std::vector<plane_t> getPlanes() const;
        std::vector<torus_t> getTorus() const;
        std::vector<tanglecube_t> getTanglecube() const;
        std::vector<triangle_t> getTriangles() const;
        std::vector<obj_t> getOBJ() const;

        PrimitivesConfig() = delete;
        PrimitivesConfig(
            const std::vector<sphere_t> &spheres,
            const std::vector<plane_t> &planes,
            const std::vector<cylinder_t> &cylinders,
            const std::vector<cone_t> &cones,
            const std::vector<torus_t> &toruses,
            const std::vector<tanglecube_t> &tanglecubes,
            const std::vector<triangle_t> &triangles,
            const std::vector<obj_t> &objs
        );
        ~PrimitivesConfig() = default;
};

} // Parser
} // raytracer

#endif //PRIMITIVESCONFIG_HPP
