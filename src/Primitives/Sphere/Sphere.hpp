//
// Created by roussierenoa on 4/28/25.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Sphere : public APrimitive {
    public:
        Sphere();
        Sphere(const Math::Point3D &position, double radius = 1.0);
        ~Sphere() = default;

        Math::hitdata_t intersect(const Math::Ray &ray) override;

        Math::Vector3D normalAt(const Math::Point3D& point) const;
        double getRadius() const;
        void setRadius(double radius);

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        double _radius;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_SPHERE_HPP
