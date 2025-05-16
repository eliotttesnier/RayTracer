//
// Created by roussierenoa on 5/1/25.
//

#ifndef ILIGHTFACTORY_HPP
#define ILIGHTFACTORY_HPP

#include <memory>
#include <map>
#include <string>
#include "LibLoader/LibLoader.hpp"
#include "Lights/ILight.hpp"

namespace RayTracer::Factory {

    class ILightFactory {
    public:
        virtual std::shared_ptr<ILight> create(const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins) const = 0;
        virtual ~ILightFactory() = default;
    };

} // namespace Raytracer::Factory

#endif // ILIGHTFACTORY_HPP
