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

            bool intersect(
                const Math::Ray &ray,
                const Math::Point3D &hitPoint,
                std::vector<std::shared_ptr<IPrimitive>> primitives
            ) const override;
            
            std::string getType() override { return "AmbientLight"; }
            
            // Implement the ambient light-specific calculation
            Graphic::color_t calculateLighting(
                const Math::hitdata_t& hitData,
                const Math::Ray& ray,
                const Math::Vector3D& viewDir
            ) const override;
    };
}

#endif //AMBIENTLIGHT_HPP
