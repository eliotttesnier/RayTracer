/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** TrianglesFactory
*/

#ifndef TRIANGLESFACTORY_HPP
#define TRIANGLESFACTORY_HPP

#include <memory>
#include <map>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Triangles/Triangles.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class TrianglesFactory : public IPrimitiveFactory {
    public:
        TrianglesFactory(
            const Math::Point3D &p1,
            const Math::Point3D &p2,
            const Math::Point3D &p3,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            const Math::Vector3D &materials
        );

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _p1;
        Math::Point3D _p2;
        Math::Point3D _p3;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        Math::Vector3D _materials;
    };

} // namespace Raytracer::Factory

#endif // TRIANGLESFACTORY_HPP
