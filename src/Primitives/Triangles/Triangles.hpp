/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** Triangles
*/

#ifndef RAYTRACER_TRIANGLES_HPP
#define RAYTRACER_TRIANGLES_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Triangles : public APrimitive {
    public:
        Triangles();
        Triangles(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3);
        ~Triangles() = default;

        Math::Vector3D getNormal() const;

        void setPoints(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3);
        void setAnchorPoint(const Math::Vector3D &anchorPoint);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        Math::Point3D _p1, _p2, _p3;
        Math::Vector3D _normal;

        Math::hitdata_t calculateTriangleIntersection(const Math::Ray &localRay) const;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_TRIANGLES_HPP
