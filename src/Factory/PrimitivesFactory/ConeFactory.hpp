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
        ConeFactory(const Math::Point3D &position, double radius, double height);

        std::unique_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _position;
        double _radius;
        double _height;
    };

} // namespace Raytracer::Factory

#endif // CONEFACTORY_HPP
