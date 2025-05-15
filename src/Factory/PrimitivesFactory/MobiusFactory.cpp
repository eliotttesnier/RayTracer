/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** MobiusFactory
*/

#include "MobiusFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Mobius/Mobius.hpp"

RayTracer::Factory::MobiusFactory::MobiusFactory(
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double majorRadius,
    double minorRadius,
    double twist,
    const std::map<std::string, std::any> &materials
):
    _majorRadius(majorRadius),
    _minorRadius(minorRadius),
    _twist(twist),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::MobiusFactory::create(
    std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Mobius") == plugins.end())
        throw std::runtime_error("Mobius plugin not found");
    auto obj = plugins["Mobius"]->initEntryPointPtr<primitive::Mobius>(
        "create",
        this->_position,
        this->_majorRadius,
        this->_minorRadius,
        this->_twist
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
