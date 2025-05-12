/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteCylinderFactory
*/

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "InfiniteCylinderFactory.hpp"
#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/InfiniteCylinder/InfiniteCylinder.hpp"

RayTracer::Factory::InfiniteCylinderFactory::InfiniteCylinderFactory(
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double radius,
    const std::vector<std::string> &materials
):
    _radius(radius),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::InfiniteCylinderFactory::create(
    std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("InfiniteCylinder") == plugins.end())
        throw std::runtime_error("InfiniteCylinder plugin not found");
    auto obj = plugins["InfiniteCylinder"]->initEntryPointPtr<primitive::InfiniteCylinder>(
        "create",
        this->_position,
        this->_radius
    );
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    obj->setShear(this->_shear);
    std::shared_ptr<RayTracer::Materials::IMaterial> material =
        RayTracer::Factory::MaterialFactory::createMaterial(
            this->_materials,
            plugins
        );
    obj->setMaterial(material);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
