//
// Created by tesniereliott on 5/6/25.
//

#include "TanglecubeFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../MaterialFactory/MaterialFactory.hpp"
#include "Primitives/Tanglecube/Tanglecube.hpp"

RayTracer::Factory::TanglecubeFactory::TanglecubeFactory(
    shading_t shading,
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    const Math::Vector3D &scale,
    const Math::Vector3D &shear,
    double size,
    const std::map<std::string, std::any> &materials
) :
    _shading(shading),
    _size(size),
    _position(position),
    _rotation(rotation),
    _scale(scale),
    _shear(shear),
    _materials(materials)
{
}

std::shared_ptr<IPrimitive> RayTracer::Factory::TanglecubeFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("Tanglecube") == plugins.end())
        throw std::runtime_error("Tanglecube plugin not found");
    auto obj = plugins.at("Tanglecube")->initEntryPointPtr<primitive::Tanglecube>(
        "create",
        this->_position,
        this->_size
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
