//
// Created by tesniereliott on 5/6/25.
//

#ifndef OBJFACTORY_HPP
#define OBJFACTORY_HPP

#include <memory>
#include <map>
#include <string>
#include <any>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/OBJ/OBJ.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class OBJFactory : public IPrimitiveFactory {
    public:
        OBJFactory(
            shading_t shading,
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            const std::string &filepath,
            const std::map<std::string, std::any> &materials
        );

        std::shared_ptr<IPrimitive> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        std::string _filepath;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, std::any> _materials;
        shading_t _shading;
    };

} // namespace RayTracer::Factory

#endif // OBJFACTORY_HPP