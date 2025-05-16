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
#include <tuple>

#include "DefaultMaterial.hpp"

namespace RayTracer::Materials
{

DefaultMaterial::DefaultMaterial(shading_t shading)
    : _wrappee(nullptr)
{
    auto [phong, ao] = shading;
    auto [ka, kd, ks, s] = phong;
    auto [rc, md] = ao;

    _ka = ka;
    _kd = kd;
    _ks = ks;
    _s = s;
    _rc = rc;
    _md = md;
}

DefaultMaterial::~DefaultMaterial() = default;

Graphic::color_t DefaultMaterial::_getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Graphic::color_t phongColor = _phongModel(hitData, ray, lights, primitives);
    double occlusion = _ambientOcclusion(hitData, primitives);
    occlusion = 0.5 + 0.5 * occlusion;
    phongColor.r *= occlusion;
    phongColor.g *= occlusion;
    phongColor.b *= occlusion;
    return phongColor;
}

Graphic::color_t DefaultMaterial::_phongModel(
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

    double ambientIntensity = 0.0;
    double diffuseIntensity = 0.0;
    double specularIntensity = 0.0;

    Math::Vector3D lightColor = {
        0.0,
        0.0,
        0.0
    };

    for (const auto &light : lights) {
        if (light->getType() == "AmbientLight") {
            const float ia = light->getIntensity();
            auto [ar, ag, ab] = light->getColor();

            ambientIntensity = ia * _ka;

            lightColor._x += (ar / 255.0) * ambientIntensity;
            lightColor._y += (ag / 255.0) * ambientIntensity;
            lightColor._z += (ab / 255.0) * ambientIntensity;
            continue;
        }

        lightInfos_t infos = light->intersect(hitData.point, primitives);

        if (infos.hit) {
            const float i = light->getIntensity();

            auto [lr, lg, lb] = light->getColor();

            Math::Vector3D L = infos.lightDir.normalized();
            Math::Vector3D N = hitData.normal.normalized();
            Math::Vector3D V = -ray.direction.normalized();
            Math::Vector3D R = N * N.dot(L) * 2.0 - L;

            double currentDiffuseIntensity = i * _kd * std::max(0.0, L.dot(N));
            double currentSpecularIntensity = i * _ks * std::pow(
                std::max(0.0, R.dot(V)), _s
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

std::tuple<Math::Vector3D, Math::Vector3D> DefaultMaterial::_orthonormalBasis(
    Math::Vector3D normal
)
{
    Math::Vector3D tangent;
    Math::Vector3D bitangent;

    if (std::abs(normal._z) < 0.999f) {
        tangent = normal.cross(Math::Vector3D(0, 0, 1)).normalized();
    } else {
        tangent = normal.cross(Math::Vector3D(0, 1, 0)).normalized();
    }
    bitangent = normal.cross(tangent).normalized();
    return std::make_tuple(tangent, bitangent);
}

float DefaultMaterial::_randomFloat() {
    return std::rand() / (RAND_MAX + 1.0f);
}

Math::Vector3D DefaultMaterial::_randomHemisphereSample(Math::Vector3D normal)
{
    float r1 = _randomFloat();
    float r2 = _randomFloat();

    float phi = 2.0f * M_PI * r1;
    float cosTheta = sqrt(1.0f - r2);
    float sinTheta = sqrt(r2);

    float x = cos(phi) * sinTheta;
    float y = sin(phi) * sinTheta;
    float z = cosTheta;

    auto [tangent, bitangent] = _orthonormalBasis(normal);

    Math::Vector3D sampleWorld = (
        tangent * x +
        bitangent * y +
        normal * z
    );
    return sampleWorld.normalized();
}

double DefaultMaterial::_ambientOcclusion(
    Math::hitdata_t hitData,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    int occludedRays = 0;
    double epsilon = 1e-4;

    for (int i = 0; i < _rc; i++) {
        Math::Vector3D dir = _randomHemisphereSample(hitData.normal);

        Math::Ray aoRay(hitData.point + hitData.normal * epsilon, dir);

        for (auto primitive : primitives) {
            Math::hitdata_t hd = primitive->intersect(aoRay);
            if (hd.hit && hd.distance < _md) {
                occludedRays += 1;
                break;
            }
        }
    }
    double occlusion = static_cast<double>(occludedRays) / static_cast<double>(_rc);
    return 1.0 - occlusion;
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

Graphic::color_t DefaultMaterial::calculateColor(
    const RayTracer::primitive::Rectangle &obj,
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
