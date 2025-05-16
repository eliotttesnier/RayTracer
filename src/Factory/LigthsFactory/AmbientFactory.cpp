//
// Created by roussierenoa on 5/1/25.
//

#include "AmbientFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <stdexcept>

#include "Lights/AmbientLight/AmbientLight.hpp"

RayTracer::Factory::AmbientFactory::AmbientFactory(double intensity,
                                                   std::tuple<int, int, int> color):
    _intensity(intensity),
    _color(color)
{
}

std::shared_ptr<ILight> RayTracer::Factory::AmbientFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("AmbientLight") == plugins.end())
        throw std::runtime_error("AmbientLight plugin not found");
    auto obj = plugins.at("AmbientLight")->initEntryPointPtr<light::AmbientLight>("create");
    auto [r, g, b] = this->_color;
    obj->setColor(r, g, b);
    obj->setIntensity(this->_intensity);
    return std::shared_ptr<ILight>(obj, [](ILight* ptr) { delete ptr; });
}
