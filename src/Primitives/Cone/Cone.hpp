/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#ifndef RAYTRACER_CONE_HPP
#define RAYTRACER_CONE_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Cone : public APrimitive {
    public:
        Cone();
        Cone(const Math::Point3D &position, double radius = 1.0, double height = 1.0);
        ~Cone() = default;

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

        Math::hitdata_t calculateConeIntersection(const Math::Ray &localRay) const;
};

} // namespace RayTracer::primitive

#endif //RAYTRACER_CONE_HPP
