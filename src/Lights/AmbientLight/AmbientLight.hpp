//
// Created by roussierenoa on 4/28/25.
//

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include "../ILight.hpp"
#include "../../Math/Ray.hpp"
#include "../../Math/Point3D.hpp"
#include "../../Lights/ALight.hpp"

namespace RayTracer::light {
    class AmbientLight : public ALight {
        public:
            AmbientLight();
            ~AmbientLight() = default;

            std::string getType() override;

            bool intersect(
                const Math::Ray &ray,
                Math::Point3D &hitPoint,
                std::vector<std::shared_ptr<IPrimitive>> primitives
            ) const override;
    };
}

#endif //AMBIENTLIGHT_HPP
