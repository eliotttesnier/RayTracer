//
// Created by roussierenoa on 5/1/25.
//

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>
#include "ConeFactory.hpp"
#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Cone/Cone.hpp"

RayTracer::Factory::ConeFactory::ConeFactory(
    shading_t shading,
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double radius,
    double height,
    const std::map<std::string, std::any> &materials
) :
    _shading(shading),
    _radius(radius),
    _height(height),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::ConeFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Cone") == plugins.end())
        throw std::runtime_error("Cone plugin not found");
    auto obj = plugins.at("Cone")->initEntryPointPtr<primitive::Cone>(
        "create",
        this->_position,
        this->_radius,
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
