/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** DefaultMaterial
*/

#include <memory>
#include <vector>
#include <algorithm>
#include <numeric>

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
        baseColor.r / 255.0,
        baseColor.g / 255.0,
        baseColor.b / 255.0,
        baseColor.a
    };

    double ka = 0.3;
    double kd = 0.5;
    double ks = 0.9;
    double shininess = 32.0;

    double ambientIntensity = 0.0;
    double diffuseIntensity = 0.0;
    double specularIntensity = 0.0;

    Math::Vector3D lightColor = {
        0.0,
        0.0,
        0.0
    };

    for (const auto& light : lights) {
        if (light->getType() == "AmbientLight") {
            float ia;
            float ar, ag, ab;
            light->getIntensity(ia);
            light->getColor(ar, ag, ab);

            ambientIntensity = ia * ka;

            lightColor._x += (ar / 255.0) * ambientIntensity;
            lightColor._y += (ag / 255.0) * ambientIntensity;
            lightColor._z += (ab / 255.0) * ambientIntensity;
            continue;
        }

        lightInfos_t infos = light->intersect(hitData.point, primitives);

        if (infos.hit) {
            float i;
            float lr, lg, lb;
            light->getIntensity(i);
            light->getColor(lr, lg, lb);

            Math::Vector3D L = infos.lightDir;
            Math::Vector3D N = hitData.normal.normalized();
            Math::Vector3D V = -ray.direction.normalized();
            Math::Vector3D R = N * N.dot(L) * 2.0 - L;

            double currentDiffuseIntensity = i * kd * std::max(0.0, L.dot(N));
            double currentSpecularIntensity = i * ks * std::pow(
                std::max(0.0, R.dot(V)), shininess
            );

            lightColor._x += (lr / 255.0) * currentDiffuseIntensity;
            lightColor._y += (lg / 255.0) * currentDiffuseIntensity;
            lightColor._z += (lb / 255.0) * currentDiffuseIntensity;
            lightColor._x += (lr / 255.0) * currentSpecularIntensity;
            lightColor._y += (lg / 255.0) * currentSpecularIntensity;
            lightColor._z += (lb / 255.0) * currentSpecularIntensity;

            diffuseIntensity += currentDiffuseIntensity;
            specularIntensity += currentSpecularIntensity;
        }
    }

    finalColor.r *= lightColor._x;
    finalColor.g *= lightColor._y;
    finalColor.b *= lightColor._z;

    finalColor.r = std::pow(finalColor.r, 1.0 / 2.2) * 255.0;
    finalColor.g = std::pow(finalColor.g, 1.0 / 2.2) * 255.0;
    finalColor.b = std::pow(finalColor.b, 1.0 / 2.2) * 255.0;

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

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::FractaleCube &obj,
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
