/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteCylinderFactory
*/

#ifndef INFINITECYLINDERFACTORY_HPP
#define INFINITECYLINDERFACTORY_HPP

#include <memory>
#include <map>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/InfiniteCylinder/InfiniteCylinder.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class InfiniteCylinderFactory : public IPrimitiveFactory {
    public:
        InfiniteCylinderFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double radius,
            const std::vector<std::string> &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _radius;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::vector<std::string> _materials;
    };

}  // namespace Raytracer::Factory

#endif // INFINITECYLINDERFACTORY_HPP
