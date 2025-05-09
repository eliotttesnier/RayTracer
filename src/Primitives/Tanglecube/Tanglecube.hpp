/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Tanglecube
*/

#ifndef RAYTRACER_TANGLECUBE_HPP
#define RAYTRACER_TANGLECUBE_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Tanglecube : public APrimitive {
    public:
        Tanglecube();
        Tanglecube(const Math::Point3D &position, double size = 1.0);
        ~Tanglecube() = default;

        double getSize() const;

        void setSize(double size);

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
        double _size;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_TANGLECUBE_HPP
