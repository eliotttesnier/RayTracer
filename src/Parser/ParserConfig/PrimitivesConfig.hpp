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
typedef std::tuple<int, int, int> color_t;

typedef std::tuple<quaduple_t, truple_t, truple_t, truple_t, color_t> sphere_t; // Position + radius, rotation, scale, shear, Color
typedef std::tuple<quintuple_t, truple_t, truple_t, truple_t, color_t> cylinder_t; // Position + radius + height, rotation, scale, shear, Color
typedef std::tuple<quintuple_t, truple_t, truple_t, truple_t, color_t> cone_t; // Position + radius + height, rotation, scale, shear, Color
typedef std::tuple<char, truple_t, truple_t, truple_t, truple_t, std::tuple<double, double>, color_t> plane_t; // axis, position, rotation, scale, shear, size, Color
typedef std::tuple<quintuple_t, truple_t, truple_t, truple_t, color_t> torus_t; // Position + major radius + minor radius, rotation, scale, shear, Color
typedef std::tuple<quaduple_t, truple_t, truple_t, truple_t, color_t> tanglecube_t; // Position + size, rotation, scale, shear, Color
typedef std::tuple<std::tuple<truple_t, truple_t, truple_t>, truple_t, truple_t, truple_t, color_t> triangle_t; // Three points (p1, p2, p3), rotation, scale, shear, Color
typedef std::tuple<std::tuple<double, double, double, std::string>, truple_t, truple_t, truple_t, color_t> obj_t; // Position + filepath, rotation, scale, shear, Color

class PrimitivesConfig {
    private:
        std::vector<sphere_t> _spheres;
        std::vector<cylinder_t> _cylinders;
        std::vector<cone_t> _cones;
        std::vector<plane_t> _planes;
        std::vector<torus_t> _toruses;
        std::vector<tanglecube_t> _tanglecubes;
        std::vector<triangle_t> _triangles;
        std::vector<obj_t> _objs;

    public:
        std::vector<sphere_t> getSpheres() const;
        std::vector<cylinder_t> getCylinders() const;
        std::vector<cone_t> getCones() const;
        std::vector<plane_t> getPlanes() const;
        std::vector<torus_t> getToruses() const;
        std::vector<tanglecube_t> getTanglecubes() const;
        std::vector<triangle_t> getTriangles() const;
        std::vector<obj_t> getOBJs() const;

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
