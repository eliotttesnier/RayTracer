//
// Created by tesniereliott on 5/6/25.
//

#ifndef TANGLECUBEFACTORY_HPP
#define TANGLECUBEFACTORY_HPP

#include <memory>
#include <map>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Tanglecube/Tanglecube.hpp"
#include "LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

    class TanglecubeFactory : public IPrimitiveFactory {
    public:
        TanglecubeFactory(const Math::Point3D &position, double size);

        std::shared_ptr<IPrimitive> create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const override;
    private:
        Math::Point3D _position;
        double _size;
    };

} // namespace Raytracer::Factory

#endif // TANGLECUBEFACTORY_HPP