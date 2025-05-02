//
// Created by roussierenoa on 5/1/25.
//

#include "DirectionalFactory.hpp"
#include "Lights/DirectionalLight/DirectionalLight.hpp"

RayTracer::Factory::DirectionalFactory::DirectionalFactory(const double intensity, const std::tuple<double, double, double> &position, const std::tuple<double, double, double> &direction, std::tuple<int, int, int> color):
    _intensity(intensity),
    _color(color),
    _position(position),
    _direction(direction)
{

}

std::unique_ptr<ILight> RayTracer::Factory::DirectionalFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("DirectionalLight"))
        throw std::runtime_error("DirectionalLight plugin not found");
    auto obj = plugins["DirectionalLight"]->initEntryPointPtr<light::DirectionalLight>("create");
    auto [r, g, b] = this->_color;
    auto [px, py, pz] = this->_position;
    auto [dx, dy, dz] = this->_direction;
    obj->setColor(r, g, b);
    obj->setIntensity(this->_intensity);
    obj->setDirection({dx, dy, dz});
    obj->setPosition(px, py, pz);
    return std::unique_ptr<ILight>(obj);
}
