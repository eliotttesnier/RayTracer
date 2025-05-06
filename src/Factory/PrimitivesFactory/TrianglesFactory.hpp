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
        TrianglesFactory(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3);

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _p1;
        Math::Point3D _p2;
        Math::Point3D _p3;
    };

} // namespace Raytracer::Factory

#endif // TRIANGLESFACTORY_HPP
