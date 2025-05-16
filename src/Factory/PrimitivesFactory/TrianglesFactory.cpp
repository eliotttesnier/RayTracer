/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** TrianglesFactory
*/

#include "TrianglesFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Triangles/Triangles.hpp"

RayTracer::Factory::TrianglesFactory::TrianglesFactory(
    shading_t shading,
    const Math::Point3D &p1,
    const Math::Point3D &p2,
    const Math::Point3D &p3,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    const std::map<std::string, std::any> &materials
) :
    _shading(shading),
    _p1(p1),
    _p2(p2),
    _p3(p3),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::TrianglesFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Triangles") == plugins.end())
        throw std::runtime_error("Triangles plugin not found");
    auto obj = plugins.at("Triangles")->initEntryPointPtr<primitive::Triangles>(
        "create",
        this->_p1,
        this->_p2,
        this->_p3
    );
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    obj->setShear(this->_shear);
    std::shared_ptr<RayTracer::Materials::IMaterial> material =
        RayTracer::Factory::MaterialFactory::createMaterial(
        _materials,
        plugins,
        _shading
    );
    obj->setMaterial(material);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
