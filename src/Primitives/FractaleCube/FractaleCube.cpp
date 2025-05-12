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

namespace RayTracer::primitive {

FractaleCube::FractaleCube()
{
    _name = "fractalecube";
    _type = "fractalecube";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _size = 1.0;
    _maxSteps = 2;
}

FractaleCube::FractaleCube(const Math::Point3D &position, double size)
{
    _name = "fractalecube";
    _type = "fractalecube";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _size = size;
    _maxSteps = 3;
}

double FractaleCube::getSize() const
{
    return _size;
}

void FractaleCube::setSize(double size)
{
    _size = size;
}

std::vector<Math::Point3D> FractaleCube::generateFractalPoints() const
{
    std::vector<Math::Point3D> points;
    points.reserve(pow(20, _maxSteps));
    points.push_back(_position);

    for (int step = 0; step < _maxSteps; ++step) {
        std::vector<Math::Point3D> newPoints;
        double newSize = _size / pow(3.0, step + 1);

        for (const auto& center : points) {
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    for (int z = -1; z <= 1; ++z) {
                        if ((abs(x) + abs(y) + abs(z)) <= 1)
                            continue;

                        newPoints.emplace_back(
                            center._x + x * newSize,
                            center._y + y * newSize,
                            center._z + z * newSize
                        );
                    }
                }
            }
        }
        points = newPoints;
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
    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = {255, 255, 255, 1.0};  // Bright magenta color for better contrast

    Math::hitdata_t mainCubeHit;
    if (!intersectCube(ray, _position, _size, mainCubeHit)) {
        return hitData;
    }

    auto points = generateFractalPoints();
    double subCubeSize = _size / pow(3, _maxSteps);
    double minDistance = std::numeric_limits<double>::max();

    for (const auto& center : points) {
        Math::hitdata_t currentHit;
        if (intersectCube(ray, center, subCubeSize, currentHit)) {
            if (currentHit.distance < minDistance) {
                minDistance = currentHit.distance;
                hitData = currentHit;
                hitData.hit = true;
                hitData.color = {255, 255, 255, 1.0};
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
