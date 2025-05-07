//
// Created by tesniereliott on 5/6/25.
//

#include "TanglecubeFactory.hpp"
#include "Primitives/Tanglecube/Tanglecube.hpp"

RayTracer::Factory::TanglecubeFactory::TanglecubeFactory(const Math::Point3D &position, const Math::Vector3D &rotation, double size):
    _position(position),
    _size(size),
    _rotation(rotation)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::TanglecubeFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("Tanglecube"))
        throw std::runtime_error("Tanglecube plugin not found");
    auto obj = plugins["Tanglecube"]->initEntryPointPtr<primitive::Tanglecube>("create", this->_position, this->_size);
    obj->setRotation(this->_rotation);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}