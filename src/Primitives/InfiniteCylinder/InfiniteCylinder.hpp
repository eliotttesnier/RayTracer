/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteCylinder
*/

#ifndef RAYTRACER_INFINITE_CYLINDER_HPP
#define RAYTRACER_INFINITE_CYLINDER_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class InfiniteCylinder : public APrimitive {
    public:
        InfiniteCylinder();
        InfiniteCylinder(const Math::Point3D &position, double radius = 1.0);
        ~InfiniteCylinder() = default;

        double getRadius() const;
        void setRadius(double radius);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        double _radius;
        Math::hitdata_t calculateInfiniteCylinderIntersection(const Math::Ray &localRay) const;
};

}

#endif
