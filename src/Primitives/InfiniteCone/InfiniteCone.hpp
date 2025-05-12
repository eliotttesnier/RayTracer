/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteCone
*/

#ifndef RAYTRACER_INFINITE_CONE_HPP
#define RAYTRACER_INFINITE_CONE_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class InfiniteCone : public APrimitive {
    public:
        InfiniteCone();
        InfiniteCone(const Math::Point3D &position, double angle = 45.0);
        ~InfiniteCone() = default;

        double getAngle() const;
        void setAngle(double angle);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        double _angle;
        Math::hitdata_t calculateInfiniteConeIntersection(const Math::Ray &localRay) const;
};

}

#endif
