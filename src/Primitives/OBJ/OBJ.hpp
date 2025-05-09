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

struct AABB {
    Math::Point3D min;
    Math::Point3D max;

    AABB() : min(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max()),
             max(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()) {}

    bool intersect(const Math::Ray &ray) const;
    void expand(const Math::Point3D &point);
};

class OBJ : public APrimitive {
    public:
        OBJ();
        OBJ(const Math::Point3D &position, const std::string &filepath);
        ~OBJ() = default;

        Math::hitdata_t intersect(const Math::Ray &ray) override;

        const std::string &getFilePath() const;
        void loadFromFile();

    private:
        std::string _filepath;
        std::vector<Math::Point3D> _vertices;
        std::vector<std::tuple<size_t, size_t, size_t>> _faces;
        std::vector<std::shared_ptr<IPrimitive>> _triangles;
        AABB _boundingBox;
        std::vector<AABB> _triangleBounds;

        bool parseOBJFile();
        void triangulatePolygon(const std::vector<size_t>& polygonIndices);
        Math::Point3D transformVertex(const Math::Point3D& vertex);
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_OBJ_HPP
