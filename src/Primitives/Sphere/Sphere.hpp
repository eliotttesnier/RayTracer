//
// Created by roussierenoa on 4/28/25.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "../IPrimitive.hpp"

namespace RayTracer::primitive {

class Sphere : public IPrimitive {
public:
    Sphere();
    Sphere(const Math::Point3D &position, double radius = 1.0);
    ~Sphere() = default;

    std::string &getName() override;
    std::string &getType() override;
    Math::Point3D &getPosition() override;
    Math::Vector3D &getRotation() override;
    Math::hitdata_t intersect(const Math::Ray &ray) override;

    Math::Vector3D normalAt(const Math::Point3D& point) const;
    double getRadius() const;
    void setRadius(double radius);

private:
    std::string _name;
    std::string _type;
    Math::Point3D _position;
    Math::Vector3D _rotation;
    double _radius;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_SPHERE_HPP
