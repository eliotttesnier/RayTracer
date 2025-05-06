//
// Created by tesniereliott on 5/6/25.
//

#include "TorusFactory.hpp"
#include "Primitives/Torus/Torus.hpp"

RayTracer::Factory::TorusFactory::TorusFactory(const Math::Point3D &position, double majorRadius, double minorRadius):
    _position(position),
    _majorRadius(majorRadius),
    _minorRadius(minorRadius)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::TorusFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const {
    if (!plugins.contains("Torus"))
        throw std::runtime_error("Torus plugin not found");
    auto obj = plugins["Torus"]->initEntryPointPtr<primitive::Torus>("create", this->_position, this->_majorRadius, this->_minorRadius);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}