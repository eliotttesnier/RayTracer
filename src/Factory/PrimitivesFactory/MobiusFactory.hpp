/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** MobiusFactory
*/

#ifndef MOBIUSFACTORY_HPP
#define MOBIUSFACTORY_HPP

#include <memory>
#include <map>
#include <any>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Mobius/Mobius.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class MobiusFactory : public IPrimitiveFactory {
    public:
        MobiusFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double majorRadius,
            double minorRadius,
            double twist,
            const std::map<std::string, std::any> &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _majorRadius;
        double _minorRadius;
        double _twist;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, std::any> _materials;
    };

} // namespace RayTracer::Factory

#endif // MOBIUSFACTORY_HPP
