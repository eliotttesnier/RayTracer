//
// Created by roussierenoa on 5/1/25.
//

#ifndef ILIGHTFACTORY_HPP
#define ILIGHTFACTORY_HPP

#include <memory>
#include "Lights/ILight.hpp"

namespace Raytracer::Factory {

    class ILightFactory {
    public:
        virtual std::unique_ptr<ILight> create() const = 0;
        virtual ~ILightFactory() = default;
    };

} // namespace Raytracer::Factory

#endif // ILIGHTFACTORY_HPP
