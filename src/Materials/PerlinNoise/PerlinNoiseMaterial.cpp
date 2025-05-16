/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** PerlinNoiseMaterial
*/

#include <cmath>
#include <algorithm>
#include <random>
#include <memory>
#include <vector>

#include "PerlinNoiseMaterial.hpp"

namespace RayTracer::Materials
{

PerlinNoiseMaterial::PerlinNoiseMaterial(
    std::shared_ptr<IMaterial> wrappee
) : _wrappee(wrappee)
{
    for (int i = 0; i < 256; ++i) {
        _perm.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_perm.begin(), _perm.end(), g);
    _perm.insert(_perm.end(), _perm.begin(), _perm.end());
    _perm.insert(_perm.end(), _perm.begin(), _perm.end());
}

PerlinNoiseMaterial::~PerlinNoiseMaterial() = default;

double PerlinNoiseMaterial::_fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoiseMaterial::_lerp(double a, double b, double t)
{
    return a + t * (b - a);
}

Math::Vector3D PerlinNoiseMaterial::_getConstantVector(int v)
{
    static const Math::Vector3D gradients[] = {
        {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
        {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
        {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
    };
    return gradients[v % 12];
}

double PerlinNoiseMaterial::_noise3d(double x, double y, double z)
{
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    double xf = x - std::floor(x);
    double yf = y - std::floor(y);
    double zf = z - std::floor(z);

    double u = _fade(xf);
    double v = _fade(yf);
    double w = _fade(zf);

    auto grad = [&](int hash, double x, double y, double z) {
        auto g = _getConstantVector(hash);
        return g._x * x + g._y * y + g._z * z;
    };

    int A = _perm[X] + Y;
    int B = _perm[X + 1] + Y;

    int AA = _perm[A] + Z;
    int AB = _perm[A + 1] + Z;
    int BA = _perm[B] + Z;
    int BB = _perm[B + 1] + Z;

    double x1, x2, y1, y2;

    x1 = _lerp(grad(_perm[AA], xf, yf, zf),
               grad(_perm[BA], xf - 1, yf, zf), u);
    x2 = _lerp(grad(_perm[AB], xf, yf - 1, zf),
               grad(_perm[BB], xf - 1, yf - 1, zf), u);
    y1 = _lerp(x1, x2, v);

    x1 = _lerp(grad(_perm[AA + 1], xf, yf, zf - 1),
               grad(_perm[BA + 1], xf - 1, yf, zf - 1), u);
    x2 = _lerp(grad(_perm[AB + 1], xf, yf - 1, zf - 1),
               grad(_perm[BB + 1], xf - 1, yf - 1, zf - 1), u);
    y2 = _lerp(x1, x2, v);

    return _lerp(y1, y2, w);
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Torus &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Tanglecube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Triangles &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::OBJ &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::FractaleCube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

Graphic::color_t PerlinNoiseMaterial::calculateColor(
    const RayTracer::primitive::Rectangle &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    Math::Point3D hitPoint = hitData.point;
    double scale = 70;
    double n = _noise3d(hitPoint._x * scale, hitPoint._y * scale, hitPoint._z * scale);
    n = std::clamp((n + 1.0) / 2.0, 0.0, 1.0);
    Graphic::color_t color = {
        n * 255,
        n * 255,
        n * 255,
        1.0
    };
    hitData.color = color;
    return _wrappee->calculateColor(
        obj,
        hitData,
        ray,
        lights,
        primitives
    );
}

}
