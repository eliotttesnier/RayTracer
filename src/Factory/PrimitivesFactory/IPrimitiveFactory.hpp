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

typedef std::tuple<double, double, double, double> phong_t;
typedef std::tuple<int, double> ambiantOcclusion_t;
typedef std::tuple<phong_t, ambiantOcclusion_t> shading_t; // Shading properties

class IPrimitiveFactory {
    public:
        virtual std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const = 0;
        virtual ~IPrimitiveFactory() = default;
    };

} // namespace Raytracer::Factory

#endif // IPRIMITIVEFACTORY_HPP
