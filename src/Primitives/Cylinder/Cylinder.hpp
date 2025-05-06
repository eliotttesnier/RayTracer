#ifndef RAYTRACER_CYLINDER_HPP
#define RAYTRACER_CYLINDER_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Cylinder : public APrimitive {
    public:
        // constructors & destructors
        Cylinder();
        Cylinder(const Math::Point3D &position, double radius = 1.0, double height = 1.0);
        ~Cylinder() = default;

        // getters
        double getRadius() const;
        double getHeight() const;

        // setters
        void setRadius(double radius);
        void setHeight(double height);

        // methods
        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

    private:
        // attributes
        double _radius;
        double _height;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_CYLINDER_HPP
