/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Torus
*/

#ifndef RAYTRACER_TORUS_HPP
#define RAYTRACER_TORUS_HPP

#include "../IPrimitive.hpp"

namespace RayTracer::primitive {

class Torus : public IPrimitive {
    public:
        Torus();
        Torus(const Math::Point3D &position, double majorRadius = 1.0, double minorRadius = 0.25);
        ~Torus() = default;

        std::string &getName() override;
        std::string &getType() override;
        Math::Point3D &getPosition() override;
        Math::Vector3D &getRotation() override;
        double getMajorRadius() const;
        double getMinorRadius() const;

        void setMajorRadius(double radius);
        void setMinorRadius(double radius);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;
        double signedDistanceFunction(const Math::Point3D& point) const;

    private:
        //attributes
        std::string _name;
        std::string _type;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        double _majorRadius;
        double _minorRadius;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_TORUS_HPP