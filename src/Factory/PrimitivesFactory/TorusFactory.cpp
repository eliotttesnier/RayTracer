//
// Created by tesniereliott on 5/6/25.
//

#include "TorusFactory.hpp"
#include "Primitives/Torus/Torus.hpp"

RayTracer::Factory::TorusFactory::TorusFactory(const Math::Point3D &position, const Math::Vector3D &rotation, const Math::Vector3D &scale, double majorRadius, double minorRadius
):
    _majorRadius(majorRadius),
    _minorRadius(minorRadius),
    _position(position),
    _rotation(rotation),
    _scale(scale)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::TorusFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("Torus"))
        throw std::runtime_error("Torus plugin not found");
    auto obj = plugins["Torus"]->initEntryPointPtr<primitive::Torus>("create", this->_position, this->_majorRadius, this->_minorRadius);
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}