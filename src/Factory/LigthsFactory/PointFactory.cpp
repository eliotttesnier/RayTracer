//
// Created by roussierenoa on 5/1/25.
//

#include "PointFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <stdexcept>

#include "Lights/PointLight/PointLight.hpp"

RayTracer::Factory::PointFactory::PointFactory(
            const double intensity,
            const std::tuple<double, double, double> &position,
            std::tuple<int, int, int> color
):
    _intensity(intensity),
    _position(position),
    _color(color)
{
}

std::shared_ptr<ILight> RayTracer::Factory::PointFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("PointLight") == plugins.end())
        throw std::runtime_error("PointLight plugin not found");
    auto obj = plugins.at("PointLight")
        ->initEntryPointPtr<light::PointLight>("create");
    auto [r, g, b] = this->_color;
    Math::Point3D pos = this->_position;
    obj->setColor(r, g, b);
    obj->setIntensity(this->_intensity);
    obj->setPosition(pos);
    return std::shared_ptr<ILight>(obj, [](ILight* ptr) { delete ptr; });
}
