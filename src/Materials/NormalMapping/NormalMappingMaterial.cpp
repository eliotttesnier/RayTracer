/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** NormalMappingMaterial
*/

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "NormalMappingMaterial.hpp"

namespace RayTracer::Materials
{

NormalMappingMaterial::NormalMappingMaterial()
    : _wrappee(nullptr), _normalMapPath(""), _normalMapIntensity(1.0f)
{
}

NormalMappingMaterial::NormalMappingMaterial(std::shared_ptr<IMaterial> wrappee,
    std::string normalMapPath)
    : _wrappee(wrappee), _normalMapPath(normalMapPath), _normalMapIntensity(1.0f)
{
    if (!_normalMapImage.loadFromFile(_normalMapPath)) {
        std::cerr << "Error: Failed to load normal map file: " << _normalMapPath << std::endl;
    } else {
        _normalMapSize.x = _normalMapImage.getSize().x;
        _normalMapSize.y = _normalMapImage.getSize().y;
        _normalMapLoaded = true;
    }
}

NormalMappingMaterial::~NormalMappingMaterial() = default;

Math::Vector3D NormalMappingMaterial::getNormalFromMap(float u, float v) const
{
    if (!_normalMapLoaded)
        return Math::Vector3D(0, 0, 1);

    float scaledU = std::fmod(u, 1.0f);
    float scaledV = std::fmod(v, 1.0f);

    if (scaledU < 0) scaledU += 1.0f;
    if (scaledV < 0) scaledV += 1.0f;

    int x = static_cast<int>(scaledU * (_normalMapSize.x - 1)) % _normalMapSize.x;
    int y = static_cast<int>(scaledV * (_normalMapSize.y - 1)) % _normalMapSize.y;

    sf::Color pixel = _normalMapImage.getPixel(x, y);

    double nx = (pixel.r / 127.5) - 1.0;
    double ny = (pixel.g / 127.5) - 1.0;
    double nz = (pixel.b / 127.5) - 1.0;

    nx *= _normalMapIntensity;
    ny *= _normalMapIntensity;
    nz = std::sqrt(1.0 - std::min(1.0, nx*nx + ny*ny));
    return Math::Vector3D(nx, ny, nz).normalized();
}

std::tuple<Math::Vector3D, Math::Vector3D> NormalMappingMaterial::createTangentSpace(
    const Math::Vector3D &normal
) const {
    Math::Vector3D up = std::abs(normal._y) < 0.999 ?
        Math::Vector3D(0, 1, 0) : Math::Vector3D(1, 0, 0);

    Math::Vector3D tangent = normal.cross(up).normalized();;
    Math::Vector3D bitangent = normal.cross(tangent).normalized();
    return std::make_tuple(tangent, bitangent);
}

Math::Vector3D NormalMappingMaterial::transformNormal(
    const Math::Vector3D &mapNormal,
    const Math::Vector3D &surfaceNormal,
    const Math::Point3D &hitPoint,
    float u, float v
) const {
    auto [tangent, bitangent] = createTangentSpace(surfaceNormal);

    return (tangent * mapNormal._x +
            bitangent * mapNormal._y +
            surfaceNormal * mapNormal._z).normalized();
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);
    float u = (theta + M_PI) / (2 * M_PI);

    double height = std::sqrt(localPoint._x * localPoint._x + localPoint._z * localPoint._z);
    float v = std::fmod(height + 10000.0, 1.0);

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);
    Math::Vector3D originalNormal = hitData.normal;

    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;

    hitData.normal = originalNormal;
    return result;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);

    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(std::abs(localPoint._y), 1.0);

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);

    Math::Vector3D originalNormal = hitData.normal;
    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;

    hitData.normal = originalNormal;
    return result;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);

    float u = std::fmod(std::abs(localPoint._x), 1.0f);
    float v = std::fmod(std::abs(localPoint._z), 1.0f);
    u = std::fmod(u * 0.35, 1.0f);
    v = std::fmod(v * 0.35, 1.0f);

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);
    Math::Vector3D originalNormal = hitData.normal;
    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;

    hitData.normal = originalNormal;
    return result;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double nx = localPoint._x;
    double ny = localPoint._y;
    double nz = localPoint._z;
    double len = std::sqrt(nx*nx + ny*ny + nz*nz);

    if (len > 0) {
        nx /= len;
        ny /= len;
        nz /= len;
    }

    double u = std::atan2(nz, nx) / (2 * M_PI) + 0.5;
    double v = std::acos(ny) / M_PI;

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);
    Math::Vector3D originalNormal = hitData.normal;
    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;

    hitData.normal = originalNormal;
    return result;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Torus &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return hitData.color;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Tanglecube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return hitData.color;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Triangles &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return hitData.color;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::OBJ &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return hitData.color;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::FractaleCube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return hitData.color;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);

    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(localPoint._y + 10000.0, 1.0);

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);
    Math::Vector3D originalNormal = hitData.normal;
    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;

    hitData.normal = originalNormal;
    return result;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);
    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(localPoint._y + 10000.0, 1.0);

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);
    Math::Vector3D originalNormal = hitData.normal;
    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;
    hitData.normal = originalNormal;
    return result;
}

Graphic::color_t NormalMappingMaterial::calculateColor(
    const RayTracer::primitive::Rectangle &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_normalMapLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);
    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(localPoint._y + 10000.0, 1.0);

    Math::Vector3D mapNormal = getNormalFromMap(u, v);
    Math::Vector3D perturbedNormal = transformNormal(mapNormal, hitData.normal,
        hitData.point, u, v);
    Math::Vector3D originalNormal = hitData.normal;
    hitData.normal = perturbedNormal;

    Graphic::color_t result;
    if (_wrappee)
        result = _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    else
        result = hitData.color;

    hitData.normal = originalNormal;
    return result;
}

}
