//
// Created by roussierenoa on 4/28/25.
//

#ifndef POINTLIGHT
#define POINTLIGHT

#include "../../Lights/ALight.hpp"
#include "../../Math/Ray.hpp"
#include "../../Math/Point3D.hpp"
#include "../../Math/Vector3D.hpp"

namespace RayTracer::light {
    class PointLight : public ALight {
    private:
        Math::Vector3D _direction;

    public:
        PointLight(const Math::Vector3D &direction = Math::Vector3D(0, -1, 0));
        ~PointLight() = default;

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

#endif //POINTLIGHT
