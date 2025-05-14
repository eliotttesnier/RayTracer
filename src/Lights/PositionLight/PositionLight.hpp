//
// Created by roussierenoa on 4/28/25.
//

#ifndef POSITIONLIGHT
#define POSITIONLIGHT

#include "../../Lights/ALight.hpp"
#include "../../Math/Ray.hpp"
#include "../../Math/Point3D.hpp"
#include "../../Math/Vector3D.hpp"

namespace RayTracer::light {
    class PositionLight : public ALight {
    private:
        Math::Vector3D _direction;

    public:
        PositionLight(const Math::Vector3D &direction = Math::Vector3D(0, -1, 0));
        ~PositionLight() = default;

        bool intersect(
            const Math::Ray &ray,
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) const override;

        void setDirection(const Math::Vector3D &direction) override;
        Math::Vector3D getDirection() const override;

        std::string getType() override { return "PositionLight"; }
    };

} // RayTracer

#endif //POSITIONLIGHT
