/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** Triangles
*/

#ifndef RAYTRACER_TRIANGLES_HPP
#define RAYTRACER_TRIANGLES_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Triangles : public APrimitive {
    public:
        // Constructors & Destructors
        Triangles();
        Triangles(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3);
        ~Triangles() = default;

        // Getters
        Math::Vector3D getNormal() const;

        // Setters
        void setPoints(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3);

        // Methods
        Math::hitdata_t intersect(const Math::Ray &ray) override;

    private:
        // Attributes
        std::string _name;
        std::string _type;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Point3D _p1, _p2, _p3;
        Math::Vector3D _normal;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_TRIANGLES_HPP
