/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** InfiniteConeFactory
*/

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "InfiniteConeFactory.hpp"
#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/InfiniteCone/InfiniteCone.hpp"

RayTracer::Factory::InfiniteConeFactory::InfiniteConeFactory(
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double angle,
    const std::vector<std::string> &materials
):
    _angle(angle),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::InfiniteConeFactory::create(
    std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("InfiniteCone") == plugins.end())
        throw std::runtime_error("InfiniteCone plugin not found");
    auto obj = plugins["InfiniteCone"]->initEntryPointPtr<primitive::InfiniteCone>(
        "create",
        this->_position,
        this->_angle
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
