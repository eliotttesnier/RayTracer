/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"

const std::string APrimitive::getName() const
{
    return _name;
}

const std::string APrimitive::getType() const
{
    return _type;
}

const Math::Point3D APrimitive::getPosition() const
{
    return _position;
}

const Math::Vector3D APrimitive::getRotation() const
{
    return _rotation;
}

void APrimitive::setName(const std::string &name)
{
    _name = name;
}

void APrimitive::setType(const std::string &type)
{
    _type = type;
}

void APrimitive::setPosition(const Math::Point3D &position)
{
    _position = position;
}

void APrimitive::setRotation(const Math::Vector3D &rotation)
{
    _rotation = rotation;
}

void APrimitive::setScale(const Math::Vector3D &scale) {
    _scale = scale;
}

Math::hitdata_t APrimitive::intersect(const Math::Ray &ray)
{
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.distance = 0.0;
    hitData.point = Math::Point3D();
    hitData.normal = Math::Vector3D();
    hitData.color = Graphic::color_t{0.0, 0.0, 0.0, 1.0};
    return hitData;
}

Graphic::color_t APrimitive::getColor(
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
            Graphic::color_t lightContribution = light->calculateLighting(hitData, ray, viewDir);

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
