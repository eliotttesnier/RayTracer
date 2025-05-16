//
// Created by roussierenoa on 5/1/25.
//

#include "CylinderFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Cylinder/Cylinder.hpp"

// TODO(roussierenoa): Utiliser Libloader pour charger les primitives

RayTracer::Factory::CylinderFactory::CylinderFactory(
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

std::shared_ptr<IPrimitive> RayTracer::Factory::CylinderFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Cylinder") == plugins.end())
        throw std::runtime_error("Cylinder plugin not found");
    auto obj = plugins.at("Cylinder")->initEntryPointPtr<primitive::Cylinder>(
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
