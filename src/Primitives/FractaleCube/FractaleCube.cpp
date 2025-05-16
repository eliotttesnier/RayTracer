/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** FractaleCube
*/

#include "FractaleCube.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <utility>
#include <tuple>

namespace RayTracer::primitive {

FractaleCube::FractaleCube()
{
    _name = "fractalecube";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _size = 1.0;
    _recursion = 3;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    double boundSize = _size * 2.5;
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-boundSize, -boundSize, -boundSize);
    _boundingBox.max = Math::Point3D(boundSize, boundSize, boundSize);
}

FractaleCube::FractaleCube(const Math::Point3D &position, double size, int recursion)
{
    _name = "fractalecube";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _size = size;
    _recursion = recursion;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    double boundSize = _size * 2.5;
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-boundSize, -boundSize, -boundSize);
    _boundingBox.max = Math::Point3D(boundSize, boundSize, boundSize);
}

double FractaleCube::getSize() const
{
    return _size;
}

void FractaleCube::setSize(double size)
{
    _size = size;
    double boundSize = _size * 2.5;
    _boundingBox.min = Math::Point3D(-boundSize, -boundSize, -boundSize);
    _boundingBox.max = Math::Point3D(boundSize, boundSize, boundSize);
}

void FractaleCube::setRecursion(int recursion)
{
    _recursion = recursion;
}

int FractaleCube::getRecursion() const
{
    return _recursion;
}

void FractaleCube::updateBoundingBox()
{
    double halfSize = _size / 2.0;
    _boundingBox.min = Math::Point3D(-halfSize, -halfSize, -halfSize);
    _boundingBox.max = Math::Point3D(halfSize, halfSize, halfSize);
}

std::vector<Math::Point3D> FractaleCube::generateFractalPoints() const
{
    const size_t estimatedSize = static_cast<size_t>(std::pow(20, _recursion));
    std::vector<Math::Point3D> points;
    points.reserve(estimatedSize);
    points.push_back(_position);

    static const std::vector<std::pair<int, std::tuple<int, int, int>>> offsets = []() {
        std::vector<std::pair<int, std::tuple<int, int, int>>> offs;
        offs.reserve(20);
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                for (int z = -1; z <= 1; ++z) {
                    int sum = std::abs(x) + std::abs(y) + std::abs(z);
                    if (sum > 1) {
                        offs.emplace_back(sum, std::make_tuple(x, y, z));
                    }
                }
            }
        }
        return offs;
    }();

    for (int step = 0; step < _recursion; ++step) {
        const double newSize = _size / std::pow(3.0, step + 1);
        const size_t currentSize = points.size();
        std::vector<Math::Point3D> newPoints;
        newPoints.reserve(currentSize * 20);

        for (const auto &center : points) {
            for (const auto &[sum, offset] : offsets) {
                const auto &[x, y, z] = offset;
                newPoints.emplace_back(
                    center._x + x * newSize,
                    center._y + y * newSize,
                    center._z + z * newSize
                );
            }
        }
        points = std::move(newPoints);
    }

    return points;
}

bool FractaleCube::intersectCube(const Math::Ray &ray,
                               const Math::Point3D &center,
                               double size,
                               Math::hitdata_t &hitData) const
{
    Math::Point3D localOrigin = ray.origin;
    Math::Vector3D halfSize(size/2, size/2, size/2);
    Math::Point3D min = center - halfSize;
    Math::Point3D max = center + halfSize;

    double tmin = (min._x - ray.origin._x) / ray.direction._x;
    double tmax = (max._x - ray.origin._x) / ray.direction._x;
    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (min._y - ray.origin._y) / ray.direction._y;
    double tymax = (max._y - ray.origin._y) / ray.direction._y;
    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    double tzmin = (min._z - ray.origin._z) / ray.direction._z;
    double tzmax = (max._z - ray.origin._z) / ray.direction._z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    if (tmin > 0) {
        hitData.distance = tmin;
        hitData.point = Math::Point3D(
            ray.origin._x + tmin * ray.direction._x,
            ray.origin._y + tmin * ray.direction._y,
            ray.origin._z + tmin * ray.direction._z
        );
        return true;
    }
    return false;
}

Math::hitdata_t FractaleCube::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = {0.0, 0.0, 0.0, 1.0};

    if (!_boundingBox.intersect(localRay))
        return hitData;

    Math::hitdata_t mainCubeHit;
    if (!intersectCube(ray, _position, _size, mainCubeHit)) {
        return hitData;
    }

    auto points = generateFractalPoints();
    double subCubeSize = _size / pow(3, _recursion);
    double minDistance = std::numeric_limits<double>::max();

    for (const auto &center : points) {
        Math::hitdata_t currentHit;
        if (intersectCube(ray, center, subCubeSize, currentHit)) {
            if (currentHit.distance < minDistance) {
                minDistance = currentHit.distance;
                hitData = currentHit;
                hitData.hit = true;
                hitData.color = _color;
            }
        }
    }

    if (hitData.hit) {
        hitData.normal = normalAt(hitData.point);
    }

    return hitData;
}

Math::Vector3D FractaleCube::normalAt(const Math::Point3D& point) const
{
    Math::Vector3D normal = Math::Vector3D(
        point._x - _position._x,
        point._y - _position._y,
        point._z - _position._z
    );
    normal.normalize();
    return normal;
}

Graphic::color_t FractaleCube::getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _material->calculateColor(
        *this,
        hitData,
        ray,
        lights,
        primitives
    );
}

}  // namespace RayTracer::primitive
