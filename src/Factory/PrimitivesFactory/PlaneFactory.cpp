//
// Created by roussierenoa on 5/1/25.
//

#include "PlaneFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <stdexcept>
#include <vector>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Plane/Plane.hpp"

RayTracer::Factory::PlaneFactory::PlaneFactory(
    shading_t shading,
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    const std::map<std::string, std::any> &materials
) :
    _shading(shading),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::PlaneFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Plane") == plugins.end())
        throw std::runtime_error("Plane plugin not found");
    auto obj = plugins.at("Plane")->initEntryPointPtr<primitive::Plane>(
        "create",
        this->_position,
        this->_rotation
    );
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
