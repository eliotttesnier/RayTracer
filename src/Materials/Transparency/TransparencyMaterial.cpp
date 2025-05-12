/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** TransparencyMaterial
*/

#include <memory>
#include <vector>

#include "TransparencyMaterial.hpp"

namespace RayTracer::Materials {

TransparencyMaterial::TransparencyMaterial(
    std::shared_ptr<IMaterial> wrappee,
    double transparency
)
    : _wrappee(wrappee), _transparency(transparency)
{
}

TransparencyMaterial::~TransparencyMaterial() = default;

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Torus &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Tanglecube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Triangles &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::OBJ &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

}
