//
// Created by roussierenoa on 5/1/25.
//

#ifndef CYLINDERFACTORY_HPP
#define CYLINDERFACTORY_HPP

#include <memory>
#include "IPrimitiveFactory.hpp"
#include "Primitives/Sphere/Sphere.hpp"

namespace RayTracer::Factory {

    class CylinderFactory : public IPrimitiveFactory {
    public:
        CylinderFactory(const Math::Point3D &position, const Math::Vector3D &rotation, const Math::Vector3D &scale, double radius, double height);

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _radius;
        double _height;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
    };

} // namespace Raytracer::Factory

#endif // CYLINDERFACTORY_HPP
