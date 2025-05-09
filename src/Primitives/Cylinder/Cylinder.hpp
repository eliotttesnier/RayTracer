/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** Cylinder
*/

#ifndef RAYTRACER_CYLINDER_HPP
#define RAYTRACER_CYLINDER_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Cylinder : public APrimitive {
    public:
        Cylinder();
        Cylinder(const Math::Point3D &position, double radius = 1.0, double height = 1.0);
        ~Cylinder() = default;

        double getRadius() const;
        double getHeight() const;

        void setRadius(double radius);
        void setHeight(double height);

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
        double _height;

        Math::hitdata_t calculateCylinderIntersection(const Math::Ray &localRay) const;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_CYLINDER_HPP
