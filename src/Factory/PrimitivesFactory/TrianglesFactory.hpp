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
#include <any>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Triangles/Triangles.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class TrianglesFactory : public IPrimitiveFactory {
    public:
        TrianglesFactory(
            shading_t shading,
            const Math::Point3D &p1,
            const Math::Point3D &p2,
            const Math::Point3D &p3,
            const Math::Vector3D &rotation,
            const Math::Vector3D &scale,
            const Math::Vector3D &shear,
            const std::map<std::string, std::any> &materials
        );

        std::shared_ptr<IPrimitive> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _p1;
        Math::Point3D _p2;
        Math::Point3D _p3;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        std::map<std::string, std::any> _materials;
        shading_t _shading;
    };

} // namespace RayTracer::Factory

#endif // TRIANGLESFACTORY_HPP
