//
// Created by tesniereliott on 5/6/25.
//

#include "OBJFactory.hpp"
#include "Primitives/OBJ/OBJ.hpp"

RayTracer::Factory::OBJFactory::OBJFactory(const Math::Point3D &position, const std::string &filepath):
    _position(position),
    _filepath(filepath)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::OBJFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("OBJ"))
        throw std::runtime_error("OBJ plugin not found");
    auto obj = plugins["OBJ"]->initEntryPointPtr<primitive::OBJ>("create", this->_position, this->_filepath);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}