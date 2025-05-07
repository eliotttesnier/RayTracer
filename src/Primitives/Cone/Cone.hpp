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

    private:
        double _radius;
        double _height;
        Math::Vector3D _anchorPoint;

        Math::Ray transformRayToLocal(const Math::Ray &ray) const;
        Math::Point3D transformPointToLocal(const Math::Point3D &point) const;
        Math::Point3D transformPointToWorld(const Math::Point3D &localPoint) const;
        Math::Vector3D transformNormalToWorld(const Math::Vector3D &localNormal) const;
        Math::hitdata_t calculateConeIntersection(const Math::Ray &localRay) const;

        void rotatePointToLocal(Math::Point3D &point, double cosX, double sinX,
                               double cosY, double sinY, double cosZ, double sinZ) const;
        void rotateVectorToLocal(Math::Vector3D &vector, double cosX, double sinX,
                                double cosY, double sinY, double cosZ, double sinZ) const;
        void rotatePointToWorld(Math::Point3D &point, double cosX, double sinX,
                               double cosY, double sinY, double cosZ, double sinZ) const;
        void rotateVectorToWorld(Math::Vector3D &vector, double cosX, double sinX,
                                double cosY, double sinY, double cosZ, double sinZ) const;
};

} // namespace RayTracer::primitive

#endif //RAYTRACER_CONE_HPP
