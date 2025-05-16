//
// Created by roussierenoa on 5/1/25.
//

#ifndef DIRECTIONAL_LIGHT_FACTORY
#define DIRECTIONAL_LIGHT_FACTORY

#include <memory>
#include <map>

#include "ILightFactory.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class DirectionalFactory : public ILightFactory {
    public:
        DirectionalFactory(double intensity, const std::tuple<double, double, double> &, const std::tuple<double, double, double> &, std::tuple<int, int, int> color);

        std::shared_ptr<ILight> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _intensity;
        std::tuple<double, double, double> _position;
        std::tuple<double, double, double> _direction;
        std::tuple<int, int, int> _color;
    };

} // namespace Raytracer::Factory

#endif // DIRECTIONALLIGHT_FACTORY
