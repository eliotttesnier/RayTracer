/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** FileTextureMaterial
*/

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "FileTextureMaterial.hpp"

namespace RayTracer::Materials
{

FileTextureMaterial::FileTextureMaterial()
    : _wrappee(nullptr), _filePath(""), _textureScale(1.0f)
{
}

FileTextureMaterial::FileTextureMaterial(std::shared_ptr<IMaterial> wrappee,
    std::string filePath)
    : _wrappee(wrappee), _filePath(filePath), _textureScale(2.5f)
{
    if (!_textureImage.loadFromFile(_filePath)) {
        std::cerr << "Error: Failed to load texture file: " << _filePath << std::endl;
    } else {
        _textureSize.x = _textureImage.getSize().x;
        _textureSize.y = _textureImage.getSize().y;
        _textureLoaded = true;
    }
}

FileTextureMaterial::~FileTextureMaterial() = default;

Graphic::color_t FileTextureMaterial::getTextureColorAtUV(float u, float v) const
{
    if (!_textureLoaded)
        return {255.0, 0.0, 255.0, 1.0};

    float scaledU = std::fmod(u * _textureScale, 1.0f);
    float scaledV = std::fmod(v * _textureScale, 1.0f);

    if (scaledU < 0) scaledU += 1.0f;
    if (scaledV < 0) scaledV += 1.0f;

    int x = static_cast<int>(scaledU * (_textureSize.x - 1)) % _textureSize.x;
    int y = static_cast<int>(scaledV * (_textureSize.y - 1)) % _textureSize.y;

    sf::Color pixel = _textureImage.getPixel(x, y);
    return {
        static_cast<double>(pixel.r),
        static_cast<double>(pixel.g),
        static_cast<double>(pixel.b),
        static_cast<double>(pixel.a) / 255.0
    };
}

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);
    float u = (theta + M_PI) / (2 * M_PI);

    double height = std::sqrt(localPoint._x * localPoint._x + localPoint._z * localPoint._z);
    float v = std::fmod(height + 10000.0, 1.0);

    Graphic::color_t textureColor = getTextureColorAtUV(u, v);
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);

    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(std::abs(localPoint._y), 1.0);

    Graphic::color_t textureColor = getTextureColorAtUV(u, v);
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    float u = std::fmod(std::abs(localPoint._x), 1.0f);
    float v = std::fmod(std::abs(localPoint._z), 1.0f);
    u = std::fmod(u * 0.35, 1.0f);
    v = std::fmod(v * 0.35, 1.0f);

    Graphic::color_t textureColor = getTextureColorAtUV(u, v);
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
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

    Graphic::color_t textureColor = getTextureColorAtUV(u, v);
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

Graphic::color_t FileTextureMaterial::calculateColor(
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

Graphic::color_t FileTextureMaterial::calculateColor(
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

Graphic::color_t FileTextureMaterial::calculateColor(
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

Graphic::color_t FileTextureMaterial::calculateColor(
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

Graphic::color_t FileTextureMaterial::calculateColor(
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

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);

    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(localPoint._y + 10000.0, 1.0);

    Graphic::color_t textureColor = getTextureColorAtUV(u, v);
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    double theta = atan2(localPoint._z, localPoint._x);
    float u = (theta + M_PI) / (2 * M_PI);
    float v = std::fmod(localPoint._y + 10000.0, 1.0);

    Graphic::color_t textureColor = getTextureColorAtUV(u, v);
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

Graphic::color_t FileTextureMaterial::calculateColor(
    const RayTracer::primitive::Rectangle &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    if (!_textureLoaded) {
        if (_wrappee)
            return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
        return hitData.color;
    }

    Math::Point3D localPoint = obj.transformPointToLocal(hitData.point);
    float u = 0.0f, v = 0.0f;

    if (std::abs(std::abs(localPoint._x) - 0.5f) < 0.001f) {
        u = (localPoint._z + 0.5f);
        v = (localPoint._y + 0.5f);
    } else if (std::abs(std::abs(localPoint._y) - 0.5f) < 0.001f) {
        u = (localPoint._x + 0.5f);
        v = (localPoint._z + 0.5f);
    } else if (std::abs(std::abs(localPoint._z) - 0.5f) < 0.001f) {
        u = (localPoint._x + 0.5f);
        v = (localPoint._y + 0.5f);
    }

    int x = static_cast<int>(u * _textureSize.x);
    int y = static_cast<int>(v * _textureSize.y);
    x = std::min(std::max(x, 0), static_cast<int>(_textureSize.x - 1));
    y = std::min(std::max(y, 0), static_cast<int>(_textureSize.y - 1));

    sf::Color pixel = _textureImage.getPixel(x, y);
    Graphic::color_t textureColor = {
        static_cast<double>(pixel.r),
        static_cast<double>(pixel.g),
        static_cast<double>(pixel.b),
        static_cast<double>(pixel.a) / 255.0
    };
    hitData.color = textureColor;

    if (_wrappee)
        return _wrappee->calculateColor(obj, hitData, ray, lights, primitives);
    return textureColor;
}

}
