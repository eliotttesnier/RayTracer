/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** RefractionMaterial
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <memory>

#include "RefractionMaterial.hpp"

namespace RayTracer::Materials {

RefractionMaterial::RefractionMaterial(
    std::shared_ptr<IMaterial> wrappee,
    double refraction
)
    : _wrappee(wrappee), _refraction(refraction), _ior(1.5)
{
}

RefractionMaterial::~RefractionMaterial() = default;

Graphic::color_t RefractionMaterial::_calculateRefractionColor(
    const Math::Ray &ray,
    const Math::Point3D &hitPoint,
    const Math::Vector3D &normal,
    bool insideObject,
    std::vector<std::shared_ptr<IPrimitive>> primitives,
    std::vector<std::shared_ptr<ILight>> lights
)
{
    Math::Vector3D normalizedDir = ray.direction.normalized();
    Math::Vector3D adjustedNormal = normal;

    double n1 = insideObject ? _ior : 1.0;
    double n2 = insideObject ? 1.0 : _ior;
    double n = n1 / n2;

    if (insideObject) {
        adjustedNormal = -adjustedNormal;
    }

    double cosI = -normalizedDir.dot(adjustedNormal);
    double sinT2 = n * n * (1.0 - cosI * cosI);

    if (sinT2 > 1.0) {
        Math::Vector3D reflectionDir = normalizedDir - adjustedNormal * (2.0 * cosI);
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

    double cosT = sqrt(1.0 - sinT2);
    Math::Vector3D refractionDir = normalizedDir * n + adjustedNormal * (n * cosI - cosT);
    refractionDir.normalize();

    Math::Ray refractionRay(hitPoint, refractionDir);

    Graphic::color_t refractionColor = {0.0, 0.0, 0.0, 1.0};
    double closestDist = std::numeric_limits<double>::max();
    bool hit = false;
    Math::hitdata_t closestHitData;
    std::shared_ptr<IPrimitive> closestPrimitive;

    for (const auto &primitive : primitives) {
        Math::hitdata_t hitData = primitive->intersect(refractionRay);
        if (hitData.hit && hitData.distance < closestDist) {
            closestDist = hitData.distance;
            closestHitData = hitData;
            closestPrimitive = primitive;
            hit = true;
        }
    }

    if (hit) {
        refractionColor = closestPrimitive->getColor(
            closestHitData,
            refractionRay,
            lights,
            primitives
        );
    }

    return refractionColor;
}

Graphic::color_t RefractionMaterial::_blendColors(
    Graphic::color_t originColor,
    Graphic::color_t refractionColor
)
{
    double mult = _refraction / 100.0;

    Graphic::color_t resultColor = {
        originColor.r * (1.0 - mult) + refractionColor.r * mult,
        originColor.g * (1.0 - mult) + refractionColor.g * mult,
        originColor.b * (1.0 - mult) + refractionColor.b * mult,
        originColor.a
    };

    return resultColor;
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

Graphic::color_t RefractionMaterial::calculateColor(
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

    bool insideObject = hitData.normal.dot(ray.direction) > 0;
    Graphic::color_t refractionColor = _calculateRefractionColor(
        ray,
        hitData.point,
        hitData.normal,
        insideObject,
        primitivesCopy,
        lights
    );

    return _blendColors(originColor, refractionColor);
}

}
