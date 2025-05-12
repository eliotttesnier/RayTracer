/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** FractaleCubeFactory
*/

#ifndef RAYTRACER_FRACTALECUBEFACTORY_HPP
#define RAYTRACER_FRACTALECUBEFACTORY_HPP

#include "IPrimitiveFactory.hpp"
#include "../Math/Point3D.hpp"
#include "../Math/Vector3D.hpp"

namespace RayTracer::Factory {

class FractaleCubeFactory : public IPrimitiveFactory {
    public:
        FractaleCubeFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            double size
        );

        std::shared_ptr<IPrimitive> create(
            std::map<std::string,
            std::unique_ptr<Loader::LibLoader>> &plugins) const override;

    private:
        double _size;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
};

}  // namespace RayTracer::Factory

#endif //RAYTRACER_FRACTALECUBEFACTORY_HPP
