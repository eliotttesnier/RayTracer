//
// Created by roussierenoa on 4/28/25.
//

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "../../Lights/ALight.hpp"
#include "../../Math/Ray.hpp"
#include "../../Math/Point3D.hpp"
#include "../../Math/Vector3D.hpp"

namespace RayTracer::light {
    class DirectionalLight : public ALight {
        private:
            Math::Vector3D _direction;

        public:
            DirectionalLight(const Math::Vector3D &direction = Math::Vector3D(0, -1, 0));
            ~DirectionalLight() = default;

            lightInfos_t intersect(
                const Math::Point3D &hitPoint,
                std::vector<std::shared_ptr<IPrimitive>> primitives
            ) const;

            void setDirection(const Math::Vector3D &direction) override;
            Math::Vector3D getDirection() const override;
            
            std::string getType() override { return "DirectionalLight"; }
    };

} // RayTracer

#endif //DIRECTIONALLIGHT_HPP
