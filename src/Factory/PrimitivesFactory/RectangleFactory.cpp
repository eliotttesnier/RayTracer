/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** RectangleFactory
*/

#include "RectangleFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Rectangle/Rectangle.hpp"

RayTracer::Factory::RectangleFactory::RectangleFactory(
    shading_t shading,
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double length,
    double width,
    double height,
    const std::map<std::string, std::any> &materials
) :
    _shading(shading),
    _length(length),
    _width(width),
    _height(height),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::RectangleFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Rectangle") == plugins.end())
        throw std::runtime_error("Rectangle plugin not found");
    auto obj = plugins.at("Rectangle")->initEntryPointPtr<primitive::Rectangle>(
        "create",
        this->_position,
        this->_length,
        this->_width,
        this->_height
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
