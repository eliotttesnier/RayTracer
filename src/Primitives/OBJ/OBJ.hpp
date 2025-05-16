/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** OBJ
*/

#ifndef RAYTRACER_OBJ_HPP
#define RAYTRACER_OBJ_HPP

#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include "../APrimitive.hpp"
#include "../IPrimitive.hpp"

namespace RayTracer::primitive {

class OBJ : public APrimitive {
    public:
        OBJ();
        OBJ(const Math::Point3D &position, const std::string &filepath);
        ~OBJ() = default;

        Math::hitdata_t intersect(const Math::Ray &ray) override;

        const std::string &getFilePath() const;
        void loadFromFile();

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        std::string _filepath;
        std::vector<Math::Point3D> _vertices;
        std::vector<std::tuple<size_t, size_t, size_t>> _faces;
        std::vector<std::shared_ptr<IPrimitive>> _triangles;
        std::vector<AABB> _triangleBounds;

        bool parseOBJFile();
        void triangulatePolygon(const std::vector<size_t> &polygonIndices);
        Math::Point3D transformVertex(const Math::Point3D& vertex);
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_OBJ_HPP
