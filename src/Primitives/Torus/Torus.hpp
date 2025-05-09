/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Torus
*/

#ifndef RAYTRACER_TORUS_HPP
#define RAYTRACER_TORUS_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Torus : public APrimitive {
    public:
        Torus();
        Torus(const Math::Point3D &position, double majorRadius = 1.0, double minorRadius = 0.25);
        ~Torus() = default;

        double getMajorRadius() const;
        double getMinorRadius() const;

        void setMajorRadius(double radius);
        void setMinorRadius(double radius);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;
        double SDF(const Math::Point3D& point) const;

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        //attributes
        double _majorRadius;
        double _minorRadius;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_TORUS_HPP