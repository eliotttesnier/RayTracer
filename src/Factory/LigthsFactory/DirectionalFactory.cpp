//
// Created by roussierenoa on 5/1/25.
//

#include "DirectionalFactory.hpp"

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <stdexcept>

#include "Lights/DirectionalLight/DirectionalLight.hpp"

RayTracer::Factory::DirectionalFactory::DirectionalFactory(
            const double intensity,
            const std::tuple<double, double, double> &position,
            const std::tuple<double, double, double> &direction,
            std::tuple<int, int, int> color
):
    _intensity(intensity),
    _color(color),
    _position(position),
    _direction(direction)
{
}

std::shared_ptr<ILight> RayTracer::Factory::DirectionalFactory::create(
    const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
) const
{
    if (plugins.find("DirectionalLight") == plugins.end())
        throw std::runtime_error("DirectionalLight plugin not found");
    auto obj = plugins.at("DirectionalLight")
        ->initEntryPointPtr<light::DirectionalLight>("create");
    auto [r, g, b] = this->_color;
    Math::Point3D pos = this->_position;
    Math::Vector3D direction = this->_direction;
    obj->setColor(r, g, b);
    obj->setIntensity(this->_intensity);
    obj->setDirection(direction);
    obj->setPosition(pos);
    return std::shared_ptr<ILight>(obj, [](ILight* ptr) { delete ptr; });
}
