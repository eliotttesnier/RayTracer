/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** DefaultMaterial
*/

#include <memory>
#include <vector>
#include <algorithm>

#include "DefaultMaterial.hpp"

namespace RayTracer::Materials
{

DefaultMaterial::DefaultMaterial()
    : _wrappee(nullptr)
{
}

DefaultMaterial::DefaultMaterial(std::shared_ptr<IMaterial> wrappee)
    : _wrappee(wrappee)
{
}

DefaultMaterial::~DefaultMaterial() = default;

Graphic::color_t DefaultMaterial::_getColor(
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
            Graphic::color_t lightContribution = light->calculateLighting(
                hitData,
                ray,
                viewDir
            );

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

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Torus &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Tanglecube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Triangles &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::OBJ &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    return _getColor(
        hitData,
        ray,
        lights,
        primitives
    );
}

}
