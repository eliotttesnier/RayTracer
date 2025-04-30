//
// Created by roussierenoa on 5/1/25.
//

#ifndef SPHEREFACTORY_HPP
#define SPHEREFACTORY_HPP

#include <memory>
#include "IPrimitiveFactory.hpp"
#include "../../Primitives/Sphere/Sphere.hpp"

namespace Raytracer::Factory {

    class SphereFactory : public IPrimitiveFactory {
    public:
        SphereFactory(const Math::Point3D &position, double radius);

        std::unique_ptr<IPrimitive> create() const override;
    private:
        Math::Point3D _position;
        double _radius;
    };

} // namespace Raytracer::Factory

#endif // SPHEREFACTORY_HPP
