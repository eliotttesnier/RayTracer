//
// Created by roussierenoa on 5/1/25.
//

#ifndef CONEFACTORY_HPP
#define CONEFACTORY_HPP

#include <memory>
#include <map>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Sphere/Sphere.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class ConeFactory : public IPrimitiveFactory {
    public:
        ConeFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double radius,
            double height,
            const std::vector<std::string> &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _radius;
        double _height;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::vector<std::string> _materials;
    };

} // namespace Raytracer::Factory

#endif // CONEFACTORY_HPP
