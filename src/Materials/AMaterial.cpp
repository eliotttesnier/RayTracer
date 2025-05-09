/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** AMaterial
*/

#include "AMaterial.hpp"
#include "Default/DefaultMaterial.hpp"

namespace RayTracer::Materials
{

AMaterial::AMaterial()
{
    _wrappee = std::make_shared<DefaultMaterial>();
}

AMaterial::AMaterial(std::shared_ptr<IMaterial> wrappee)
    : _wrappee(wrappee)
{
}

Graphic::color_t AMaterial::_getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (lights.empty()) {
        return hitData.color;
    }

    Graphic::color_t baseColor = hitData.color;
    
    Graphic::color_t finalColor = {
        baseColor.r * 0.05,
        baseColor.g * 0.05,
        baseColor.b * 0.05,
        baseColor.a
    };
    
    Math::Vector3D viewDir = -ray.direction.normalized();
    
    for (const auto& light : lights) {
        if (light->intersect(ray, hitData.point, primitives)) {
            Graphic::color_t lightContribution = light->calculateLighting(hitData, ray, viewDir);
            
            finalColor.r += lightContribution.r;
            finalColor.g += lightContribution.g;
            finalColor.b += lightContribution.b;
        }
    }
    
    finalColor.r = std::pow(finalColor.r / 255.0, 1.0 / 2.2) * 255.0;
    finalColor.g = std::pow(finalColor.g / 255.0, 1.0 / 2.2) * 255.0;
    finalColor.b = std::pow(finalColor.b / 255.0, 1.0 / 2.2) * 255.0;
    
    finalColor.r = std::max(0.0, std::min(255.0, finalColor.r));
    finalColor.g = std::max(0.0, std::min(255.0, finalColor.g));
    finalColor.b = std::max(0.0, std::min(255.0, finalColor.b));
    
    return finalColor;
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Cone obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Cylinder obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Plane obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Sphere obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Torus obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Tanglecube obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::Triangles obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

Graphic::color_t AMaterial::calculateColor(
    RayTracer::primitive::OBJ obj,
    infos_t infos
)
{
    return _getColor(
        infos.hitData,
        infos.ray,
        infos.lights,
        infos.primitives
    );
}

}
