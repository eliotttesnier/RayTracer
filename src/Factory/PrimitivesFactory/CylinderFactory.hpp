//
// Created by roussierenoa on 5/1/25.
//

#ifndef CYLINDERFACTORY_HPP
#define CYLINDERFACTORY_HPP

#include <memory>
#include <map>
#include "IPrimitiveFactory.hpp"
#include "Primitives/Sphere/Sphere.hpp"

namespace RayTracer::Factory {

    class CylinderFactory : public IPrimitiveFactory {
    public:
        CylinderFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double radius, double height,
            const std::map<std::string, double> &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _radius;
        double _height;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, double> _materials;
    };

} // namespace RayTracer::Factory

#endif // CYLINDERFACTORY_HPP
