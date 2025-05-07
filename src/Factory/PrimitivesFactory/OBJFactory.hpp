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
        OBJFactory(const Math::Point3D &position, const Math::Vector3D &rotation, const std::string &filepath);

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _position;
        Math::Vector3D _rotation;
        std::string _filepath;
    };

} // namespace Raytracer::Factory

#endif // OBJFACTORY_HPP