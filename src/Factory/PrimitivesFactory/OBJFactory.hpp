//
// Created by tesniereliott on 5/6/25.
//

#ifndef OBJFACTORY_HPP
#define OBJFACTORY_HPP

#include <memory>
#include <map>
#include <string>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/OBJ/OBJ.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class OBJFactory : public IPrimitiveFactory {
    public:
        OBJFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            const std::string &filepath,
            const Math::Vector3D &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        std::string _filepath;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        Math::Vector3D _materials;
    };

} // namespace Raytracer::Factory

#endif // OBJFACTORY_HPP