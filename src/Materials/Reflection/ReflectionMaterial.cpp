/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** ReflectionMaterial
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <memory>

#include "ReflectionMaterial.hpp"

namespace RayTracer::Materials {

ReflectionMaterial::ReflectionMaterial(
    std::shared_ptr<IMaterial> wrappee,
    double reflection
)
    : _wrappee(wrappee), _reflection(reflection)
{
}

ReflectionMaterial::~ReflectionMaterial() = default;

Graphic::color_t ReflectionMaterial::_calculateReflectionColor(
    const Math::Ray &ray,
    const Math::Point3D &hitPoint,
    const Math::Vector3D &normal,
    std::vector<std::shared_ptr<IPrimitive>> primitives,
    std::vector<std::shared_ptr<ILight>> lights
)
{
    Math::Vector3D normalizedDir = ray.direction.normalized();
    double dotProduct = normalizedDir.dot(normal);
    Math::Vector3D reflectionDir = normalizedDir - normal * (2.0 * dotProduct);
    reflectionDir.normalize();

    Math::Ray reflectionRay(hitPoint, reflectionDir);

    Graphic::color_t reflectionColor = {0.0, 0.0, 0.0, 1.0};
    double closestDist = std::numeric_limits<double>::max();
    bool hit = false;
    Math::hitdata_t closestHitData;
    std::shared_ptr<IPrimitive> closestPrimitive;

    for (const auto &primitive : primitives) {
        Math::hitdata_t hitData = primitive->intersect(reflectionRay);

        if (hitData.hit && hitData.distance < closestDist) {
            closestDist = hitData.distance;
            closestHitData = hitData;
            closestPrimitive = primitive;
            hit = true;
        }
    }

    if (hit) {
        reflectionColor = closestPrimitive->getColor(
            closestHitData,
            reflectionRay,
            lights,
            primitives
        );
    }

    return reflectionColor;
}

Graphic::color_t ReflectionMaterial::_blendColors(
    Graphic::color_t originColor,
    Graphic::color_t reflectionColor
)
{
    double mult = _reflection / 100.0;

    Graphic::color_t resultColor = {
        originColor.r * (1.0 - mult) + reflectionColor.r * mult,
        originColor.g * (1.0 - mult) + reflectionColor.g * mult,
        originColor.b * (1.0 - mult) + reflectionColor.b * mult,
        originColor.a
    };

    return resultColor;
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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
            return
            dynamic_cast<RayTracer::primitive::InfiniteCylinder *>(primitive.get()) == &obj;
        }),
        primitivesCopy.end()
    );

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

Graphic::color_t ReflectionMaterial::calculateColor(
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

    Graphic::color_t reflectionColor = _calculateReflectionColor(
        ray,
        hitData.point,
        hitData.normal,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, reflectionColor);
}

}
