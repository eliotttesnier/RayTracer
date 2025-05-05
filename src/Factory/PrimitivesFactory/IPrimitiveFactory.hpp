//
// Created by roussierenoa on 5/1/25.
//

#ifndef IPRIMITIVEFACTORY_HPP
#define IPRIMITIVEFACTORY_HPP

#include <memory>
#include <map>
#include "LibLoader/LibLoader.hpp"
#include "Primitives/IPrimitive.hpp"

namespace RayTracer::Factory {

    class IPrimitiveFactory {
    public:
        virtual std::unique_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const = 0;
        virtual ~IPrimitiveFactory() = default;
    };

} // namespace Raytracer::Factory

#endif // IPRIMITIVEFACTORY_HPP
