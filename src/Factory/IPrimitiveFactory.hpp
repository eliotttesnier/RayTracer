//
// Created by roussierenoa on 5/1/25.
//

#ifndef IPRIMITIVEFACTORY_HPP
#define IPRIMITIVEFACTORY_HPP

#include <memory>
#include "../Primitives/IPrimitive.hpp"

namespace Raytracer::Factory {

    class IPrimitiveFactory {
    public:
        virtual std::unique_ptr<IPrimitive> create() const = 0;
        virtual ~IPrimitiveFactory() = default;
    };

} // namespace Raytracer::Factory

#endif // IPRIMITIVEFACTORY_HPP
