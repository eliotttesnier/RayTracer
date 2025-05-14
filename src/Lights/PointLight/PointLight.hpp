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

    public:
        lightInfos_t intersect(
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives) const override;

        std::string getType() override { return this->_lightName; }

        PointLight(const Math::Point3D &pos = Math::Point3D(0, -1, 0));
        ~PointLight() = default;
    };

} // RayTracer

#endif //POINTLIGHT
