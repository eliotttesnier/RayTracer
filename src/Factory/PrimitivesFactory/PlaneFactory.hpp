//
// Created by roussierenoa on 5/1/25.
//

#ifndef PLANEFACTORY_HPP
#define PLANEFACTORY_HPP

#include <memory>
#include <map>
#include <any>
#include "IPrimitiveFactory.hpp"

namespace RayTracer::Factory {

class PlaneFactory : public IPrimitiveFactory {
    public:
        PlaneFactory(
            shading_t shading,
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            const std::map<std::string, std::any> &materials
        );

        std::shared_ptr<IPrimitive> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, std::any> _materials;
        shading_t _shading;
    };

} // namespace RayTracer::Factory

#endif // PLANEFACTORY_HPP
