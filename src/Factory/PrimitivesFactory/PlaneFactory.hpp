//
// Created by roussierenoa on 5/1/25.
//

#ifndef PLANEFACTORY_HPP
#define PLANEFACTORY_HPP

#include <memory>
#include "IPrimitiveFactory.hpp"

namespace Raytracer::Factory {

    class PlaneFactory : public IPrimitiveFactory {
    public:
        PlaneFactory(const Math::Point3D &position, const Math::Vector3D &rotation);

        std::unique_ptr<IPrimitive> create() const override;
    private:
        Math::Point3D _position;
        Math::Vector3D _rotation;
    };

} // namespace Raytracer::Factory

#endif // PLANEFACTORY_HPP
