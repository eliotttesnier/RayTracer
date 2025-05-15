/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Mobius
*/

#ifndef RAYTRACER_MOBIUS_HPP
#define RAYTRACER_MOBIUS_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Mobius : public APrimitive {
    public:
        Mobius();
        Mobius(const Math::Point3D &position, double majorRadius = 1.0, double minorRadius = 0.25, double twist = 1.0);
        ~Mobius() = default;

        double getMajorRadius() const;
        double getMinorRadius() const;
        double getTwist() const;

        void setMajorRadius(double radius);
        void setMinorRadius(double radius);
        void setTwist(double twist);

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
        double _majorRadius;
        double _minorRadius;
        double _twist;
};

} // namespace RayTracer::primitive

#endif //RAYTRACER_MOBIUS_HPP