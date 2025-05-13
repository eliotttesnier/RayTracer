/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** FractaleCubeFactory
*/

#ifndef RAYTRACER_FRACTALECUBEFACTORY_HPP
#define RAYTRACER_FRACTALECUBEFACTORY_HPP

#include <memory>
#include <map>
#include <vector>
#include <string>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/FractaleCube/FractaleCube.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class FractaleCubeFactory : public IPrimitiveFactory {
    public:
        FractaleCubeFactory(
            const Math::Point3D &position,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            double size,
            int recursion,
            const std::map<std::string, double> &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _size;
        int _recursion;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, double> _materials;
    };

}  // namespace RayTracer::Factory

#endif //RAYTRACER_FRACTALECUBEFACTORY_HPP
