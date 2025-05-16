//
// Created by roussierenoa on 5/1/25.
//

#ifndef AMBIENTLIGHTFACTORY_HPP
#define AMBIENTLIGHTFACTORY_HPP

#include <memory>
#include <map>

#include "ILightFactory.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class AmbientFactory : public ILightFactory {
    public:
        AmbientFactory(double intensity, std::tuple<int, int, int> color);

        std::shared_ptr<ILight> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        double _intensity;
        std::tuple<int, int, int> _color;
    };

} // namespace Raytracer::Factory

#endif // AMBIENTLIGHTFACTORY_HPP
