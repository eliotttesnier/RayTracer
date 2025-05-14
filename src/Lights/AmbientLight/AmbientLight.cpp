//
// Created by roussierenoa on 4/28/25.
//

#include "AmbientLight.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

RayTracer::light::AmbientLight::AmbientLight()
{
    this->_lightName = "AmbientLight";
}

lightInfos_t RayTracer::light::AmbientLight::intersect(
    const Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives
) const
{
    (void)hitPoint;
    (void)primitives;
    lightInfos_t infos;
    infos.hit = true;
    infos.lightDir = Math::Vector3D();
    return infos;
}
