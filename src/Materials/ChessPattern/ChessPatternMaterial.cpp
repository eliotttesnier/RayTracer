/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** ChessPatternMaterial
*/

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>

#include "ChessPatternMaterial.hpp"

namespace RayTracer::Materials
{

ChessPatternMaterial::ChessPatternMaterial()
    : _wrappee(nullptr), _scale(1.0)
{
    _colorWhite = {255.0, 255.0, 255.0, 1.0};
    _colorBlack = {0.0, 0.0, 0.0, 1.0};
}

ChessPatternMaterial::ChessPatternMaterial(std::shared_ptr<IMaterial> wrappee)
    : _wrappee(wrappee), _scale(1.0)
{
    _colorWhite = {255.0, 255.0, 255.0, 1.0};
    _colorBlack = {0.0, 0.0, 0.0, 1.0};
}

ChessPatternMaterial::~ChessPatternMaterial() = default;

Graphic::color_t ChessPatternMaterial::_applyChessPattern(
    const Math::Point3D &hitPoint,
    Graphic::color_t baseColor
)
{
    double x = std::round(hitPoint._x / _scale);
    double y = std::round(hitPoint._y / _scale);
    double z = std::round(hitPoint._z / _scale);

    bool isWhite = (static_cast<int>(x + y + z)) % 2 == 0;

    return isWhite ? _colorWhite : _colorBlack;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Cone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Cylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Plane &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Sphere &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Torus &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Tanglecube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::Triangles &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::OBJ &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::FractaleCube &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCone &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

Graphic::color_t ChessPatternMaterial::calculateColor(
    const RayTracer::primitive::InfiniteCylinder &obj,
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    (void) obj;
    Graphic::color_t color = _applyChessPattern(
        hitData.point,
        hitData.color
    );
    hitData.color = color;

    if (_wrappee != nullptr) {
        return _wrappee->calculateColor(
            obj,
            hitData,
            ray,
            lights,
            primitives
        );
    }
    return color;
}

}
