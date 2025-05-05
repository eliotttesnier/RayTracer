//
// Created by roussierenoa on 5/1/25.
//

#include "AmbientFactory.hpp"
#include "Lights/AmbientLight/AmbientLight.hpp"

RayTracer::Factory::AmbientFactory::AmbientFactory(double intensity, std::tuple<int, int, int> color):
    _intensity(intensity),
    _color(color)
{

}

std::shared_ptr<ILight> RayTracer::Factory::AmbientFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("AmbientLight"))
        throw std::runtime_error("AmbientLight plugin not found");
    auto obj = plugins["AmbientLight"]->initEntryPointPtr<light::AmbientLight>("create");
    auto [r, g, b] = this->_color;
    obj->setColor(r, g, b);
    obj->setIntensity(this->_intensity);
    return std::shared_ptr<ILight>(obj, [](ILight* ptr) { delete ptr; });
}
