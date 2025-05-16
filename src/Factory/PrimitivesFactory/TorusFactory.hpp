//
// Created by tesniereliott on 5/6/25.
//

#ifndef TORUSFACTORY_HPP
#define TORUSFACTORY_HPP

#include <memory>
#include <map>
#include <any>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Torus/Torus.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class TorusFactory : public IPrimitiveFactory {
    public:
        TorusFactory(
            shading_t shading,
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double majorRadius,
            double minorRadius,
            const std::map<std::string, std::any> &materials
        );

        std::shared_ptr<IPrimitive> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _majorRadius;
        double _minorRadius;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, std::any> _materials;
        shading_t _shading;
    };

} // namespace RayTracer::Factory

#endif // TORUSFACTORY_HPP