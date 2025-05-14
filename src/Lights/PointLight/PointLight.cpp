//
// Created by roussierenoa on 4/28/25.
//

#include "PointLight.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

namespace RayTracer::light {

    PointLight::PointLight(const Math::Point3D &position):
        ALight()
    {
        this->_position = position;
        this->_lightName = "PositionLight";
    }

    lightInfos_t PointLight::intersect(
        const Math::Point3D &hitPoint,
        std::vector<std::shared_ptr<IPrimitive>> primitives
    ) const
    {
        Math::Vector3D lightDir(
            _position._x - hitPoint._x,
            _position._y - hitPoint._y,
            _position._z - hitPoint._z
        );

        double distanceToLight = lightDir.length();
        lightDir = lightDir.normalized();
        lightInfos_t infos;
        infos.lightDir = lightDir;
        infos.hit = true;
        return infos;
    }

}  // namespace RayTracer::light
