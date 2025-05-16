//
// Created by roussierenoa on 4/30/25.
//

#ifndef PRIMITIVESCONFIG_HPP
#define PRIMITIVESCONFIG_HPP

#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include <map>
#include <any>

namespace RayTracer {
namespace Parser {

typedef std::tuple<double, double> duotuple_t;
typedef std::tuple<double, double, double> truple_t;
typedef std::tuple<double, double, double, double> quaduple_t;
typedef std::tuple<double, double, double, double, double> quintuple_t;
typedef std::tuple<int, int, int> color_t;

typedef quaduple_t phong_t;
typedef std::tuple<int, double> ambientOcclusion_t;

typedef std::map<std::string, std::any> material_t; // Material properties
typedef std::tuple<phong_t, ambientOcclusion_t> shading_t; // Shading properties

typedef std::tuple<shading_t, material_t, double, truple_t, truple_t, truple_t, truple_t, color_t> sphere_t; // Material, radius, Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, duotuple_t, truple_t, truple_t, truple_t, truple_t, color_t> cylinder_t; // Material, radius + height, Position , rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, duotuple_t, truple_t, truple_t, truple_t, truple_t, color_t> cone_t; // Material, radius + height, Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, char, truple_t, truple_t, truple_t, truple_t, color_t> plane_t; // Material, axis, position, rotation, scale, shear, size, Color
typedef std::tuple<shading_t, material_t, duotuple_t, truple_t, truple_t, truple_t, truple_t, color_t> torus_t; // Material,  major radius + minor radius, Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, double, truple_t, truple_t, truple_t, truple_t, color_t> tanglecube_t; // Material, size, Position , rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, std::tuple<truple_t, truple_t, truple_t>, truple_t, truple_t, truple_t, color_t> triangle_t; // Material, Three points (p1, p2, p3), rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, std::string, truple_t, truple_t, truple_t, truple_t, color_t> obj_t; // Material, filepath, Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, double, int, truple_t, truple_t, truple_t, truple_t, color_t> fractalecube_t; // Material, size, recursion, Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, double, truple_t, truple_t, truple_t, truple_t, color_t> infinitecone_t; // Material, radius, Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, double, truple_t, truple_t, truple_t, truple_t, color_t> infinitecylinder_t; // Material, radius , Position, rotation, scale, shear, Color
typedef std::tuple<shading_t, material_t, truple_t, truple_t, truple_t, truple_t, truple_t, color_t> rectangle_t; // Material, dimensions (length, width, height), Position, rotation, scale, shear, Color

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
        std::vector<infinitecone_t> _infiniteCones;
        std::vector<infinitecylinder_t> _infiniteCylinders;
        std::vector<fractalecube_t> _fractalecubes;
        std::vector<rectangle_t> _rectangles;

    public:
        std::vector<sphere_t> getSpheres() const;
        std::vector<cylinder_t> getCylinders() const;
        std::vector<cone_t> getCones() const;
        std::vector<plane_t> getPlanes() const;
        std::vector<torus_t> getToruses() const;
        std::vector<tanglecube_t> getTanglecubes() const;
        std::vector<triangle_t> getTriangles() const;
        std::vector<obj_t> getOBJs() const;
        std::vector<infinitecone_t> getInfiniteCones() const;
        std::vector<infinitecylinder_t> getInfiniteCylinders() const;
        std::vector<fractalecube_t> getFractaleCubes() const;
        std::vector<rectangle_t> getRectangles() const;

        PrimitivesConfig() = delete;
        PrimitivesConfig(
            const std::vector<sphere_t> &spheres,
            const std::vector<plane_t> &planes,
            const std::vector<cylinder_t> &cylinders,
            const std::vector<cone_t> &cones,
            const std::vector<torus_t> &toruses,
            const std::vector<tanglecube_t> &tanglecubes,
            const std::vector<triangle_t> &triangles,
            const std::vector<obj_t> &objs,
            const std::vector<infinitecylinder_t> &infiniteCylinders,
            const std::vector<infinitecone_t> &infiniteCones,
            const std::vector<fractalecube_t> &fractalecubes,
            const std::vector<rectangle_t> &rectangles
        );
        ~PrimitivesConfig() = default;
};

} // Parser
} // raytracer

#endif //PRIMITIVESCONFIG_HPP
