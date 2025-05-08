//
// Created by roussierenoa on 5/1/25.
//

#ifndef SPHEREFACTORY_HPP
#define SPHEREFACTORY_HPP

#include <memory>
#include "IPrimitiveFactory.hpp"

namespace RayTracer::Factory {

    class SphereFactory : public IPrimitiveFactory {
    public:
        SphereFactory(const Math::Point3D &position, const Math::Vector3D &rotation, const Math::Vector3D &scale, double radius);

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _radius;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
    };

} // namespace Raytracer::Factory

#endif // SPHEREFACTORY_HPP
