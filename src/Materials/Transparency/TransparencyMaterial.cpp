/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** TransparencyMaterial
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <memory>

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

Graphic::color_t TransparencyMaterial::_calculateRatioColor(
    Graphic::color_t origin,
    Graphic::color_t behind
)
{
    double mult = _transparency / 100.0;

    Graphic::color_t resultColor = {
        behind.r * mult
        + origin.r * (1.0 - mult),
        behind.g * mult
        + origin.g * (1.0 - mult),
        behind.b * mult
        + origin.b * (1.0 - mult),
        behind.a * mult
        + origin.a * (1.0 - mult),
    };
    return resultColor;
}

Graphic::color_t TransparencyMaterial::_getBehindColor(
    const Math::Ray &ray,
    const Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives,
    std::vector<std::shared_ptr<ILight>> lights
)
{
    Graphic::color_t behindColor = {0.0, 0.0, 0.0, 1.0};

    double closestDist = std::numeric_limits<double>::max();
    bool hit = false;
    Math::hitdata_t closestHitData;
    std::shared_ptr<IPrimitive> closestPrimitive;

    for (const auto &primitive : primitives) {
        Math::hitdata_t hitData = primitive->intersect(ray);

        if (hitData.hit && hitData.distance < closestDist) {
            closestDist = hitData.distance;
            closestHitData = hitData;
            closestPrimitive = primitive;
            hit = true;
        }
    }

    if (hit) {
        behindColor = closestPrimitive->getColor(
            closestHitData,
            ray,
            lights,
            primitives
        );
    }
    return behindColor;
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Cone *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Cylinder *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Plane *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Sphere *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Torus &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Torus *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Tanglecube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Tanglecube *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Triangles &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::Triangles *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::OBJ &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::OBJ *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::FractaleCube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::FractaleCube *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::InfiniteCone *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive> &primitive) {
            return dynamic_cast<RayTracer::primitive::InfiniteCylinder *>(
                primitive.get()
            ) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

Graphic::color_t TransparencyMaterial::calculateColor(
    const RayTracer::primitive::Rectangle &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t originColor = _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );

    std::vector<std::shared_ptr<IPrimitive>> primitivesCopy = primitives;
    primitivesCopy.erase(
        std::remove_if(primitivesCopy.begin(), primitivesCopy.end(),
        [&obj](const std::shared_ptr<IPrimitive>& primitive) {
            return dynamic_cast<RayTracer::primitive::Rectangle *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t behindColor = _getBehindColor(
        ray,
        hitData.point,
        primitivesCopy,
        lights
    );

    return _calculateRatioColor(originColor, behindColor);
}

}
