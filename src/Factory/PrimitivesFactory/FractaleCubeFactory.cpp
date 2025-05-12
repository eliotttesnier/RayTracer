/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** FractaleCubeFactory
*/

#include "FractaleCubeFactory.hpp"

#include <map>
#include <memory>
#include <string>

#include "Primitives/FractaleCube/FractaleCube.hpp"

RayTracer::Factory::FractaleCubeFactory::FractaleCubeFactory(
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    double size
):
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _size(size)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::FractaleCubeFactory::create(
    std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
) const
{
    if (!plugins.contains("FractaleCube"))
        throw std::runtime_error("FractaleCube plugin not found");
    auto obj = plugins["FractaleCube"]->initEntryPointPtr<primitive::FractaleCube>(
        "create",
        this->_position,
        this->_size
    );
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
