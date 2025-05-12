//
// Created by tesniereliott on 5/6/25.
//

#ifndef TANGLECUBEFACTORY_HPP
#define TANGLECUBEFACTORY_HPP

#include <memory>
#include <map>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Tanglecube/Tanglecube.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class TanglecubeFactory : public IPrimitiveFactory {
    public:
        TanglecubeFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double size,
            const Math::Vector3D &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _size;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        Math::Vector3D _materials;
    };

} // namespace Raytracer::Factory

#endif // TANGLECUBEFACTORY_HPP