//
// Created by tesniereliott on 5/6/25.
//

#include "TorusFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>
#include <any>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Torus/Torus.hpp"

RayTracer::Factory::TorusFactory::TorusFactory(
    shading_t shading,
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double majorRadius,
    double minorRadius,
    const std::map<std::string, std::any> &materials
) :
    _shading(shading),
    _majorRadius(majorRadius),
    _minorRadius(minorRadius),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::TorusFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Torus") == plugins.end())
        throw std::runtime_error("Torus plugin not found");
    auto obj = plugins.at("Torus")->initEntryPointPtr<primitive::Torus>(
        "create",
        this->_position,
        this->_majorRadius,
        this->_minorRadius
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
