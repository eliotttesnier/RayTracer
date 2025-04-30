//
// Created by roussierenoa on 4/28/25.
//

#ifndef PLANE_HPP
#define PLANE_HPP

#include "../IPrimitive.hpp"
#include "../../Math/Rectangle3D.hpp"

namespace Raytracer::primitive {

class Plane : public IPrimitive {
public:
    Plane();
    Plane(const Math::Point3D &position, const Math::Vector3D &rotation);
    ~Plane() = default;

    std::string &getName() override;
    std::string &getType() override;
    Math::Point3D &getPosition() override;
    Math::Vector3D &getRotation() override;
    Math::hitdata_t intersect(const Math::Ray &ray) override;

private:
    std::string _name;
    std::string _type;
    Math::Point3D _position;
    Math::Vector3D _rotation;
    RayTracer::Rectangle3D _rectangle;
};

} // Raytracer

#endif //PLANE_HPP
