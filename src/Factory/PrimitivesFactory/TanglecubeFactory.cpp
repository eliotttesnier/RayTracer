//
// Created by tesniereliott on 5/6/25.
//

#include "TanglecubeFactory.hpp"
#include "Primitives/Tanglecube/Tanglecube.hpp"

RayTracer::Factory::TanglecubeFactory::TanglecubeFactory(const Math::Point3D &position, const Math::Vector3D &rotation, const Math::Vector3D &scale, double size
):
    _size(size),
    _position(position),
    _rotation(rotation),
    _scale(scale)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::TanglecubeFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("Tanglecube"))
        throw std::runtime_error("Tanglecube plugin not found");
    auto obj = plugins["Tanglecube"]->initEntryPointPtr<primitive::Tanglecube>("create", this->_position, this->_size);
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}