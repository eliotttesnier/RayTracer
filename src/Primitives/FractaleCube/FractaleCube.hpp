/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** FractaleCube
*/

#ifndef RAYTRACER_FRACTALECUBE_HPP
#define RAYTRACER_FRACTALECUBE_HPP

#include "../APrimitive.hpp"
#include <vector>

namespace RayTracer::primitive {

class FractaleCube : public APrimitive {
    public:
        FractaleCube();
        FractaleCube(const Math::Point3D &position, double size = 1.0, int recursion = 3);
        ~FractaleCube() = default;

        double getSize() const;
        void setSize(double size);
        void setRecursion(int recursion);
        int getRecursion() const;
        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        double _size;
        int _recursion;
        void updateBoundingBox();
        std::vector<Math::Point3D> generateFractalPoints() const;
        Math::Vector3D normalAt(const Math::Point3D& point) const;
        bool intersectCube(
            const Math::Ray &ray,
            const Math::Point3D &center,
            double size,
            Math::hitdata_t &hitData
        ) const;
};

}  // namespace RayTracer::primitive

#endif //RAYTRACER_FRACTALECUBE_HPP
