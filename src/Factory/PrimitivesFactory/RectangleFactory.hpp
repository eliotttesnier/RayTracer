/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** RectangleFactory
*/

#ifndef RECTANGLEFACTORY_HPP
#define RECTANGLEFACTORY_HPP

#include <memory>
#include <map>
#include <any>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Rectangle/Rectangle.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class RectangleFactory : public IPrimitiveFactory {
    public:
        RectangleFactory(
            shading_t shading,
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double length,
            double width,
            double height,
            const std::map<std::string, std::any> &materials
        );

        std::shared_ptr<IPrimitive> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _length;
        double _width;
        double _height;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, std::any> _materials;
        shading_t _shading;
    };

}  // namespace RayTracer::Factory

#endif // RECTANGLEFACTORY_HPP
