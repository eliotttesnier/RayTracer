/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Tanglecube
*/

#ifndef RAYTRACER_TANGLECUBE_HPP
#define RAYTRACER_TANGLECUBE_HPP

#include "../IPrimitive.hpp"

namespace RayTracer::primitive {

class Tanglecube : public IPrimitive {
    public:
        Tanglecube();
        Tanglecube(const Math::Point3D &position, double size = 1.0);
        ~Tanglecube() = default;

        std::string &getName() override;
        std::string &getType() override;
        Math::Point3D &getPosition() override;
        Math::Vector3D &getRotation() override;
        double getSize() const;

        void setSize(double size);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;
        double signedDistanceFunction(const Math::Point3D& point) const;

    private:
        //attributes
        std::string _name;
        std::string _type;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        double _size;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_TANGLECUBE_HPP