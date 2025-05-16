/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Rectangle
*/

#ifndef RAYTRACER_RECTANGLE_HPP
#define RAYTRACER_RECTANGLE_HPP

#include "../APrimitive.hpp"

namespace RayTracer::primitive {

class Rectangle : public APrimitive {
    public:
        Rectangle();
        Rectangle(const Math::Point3D &position, double length = 1.0, double width = 1.0, double height = 1.0);
        ~Rectangle() = default;

        double getLength() const;
        double getWidth() const;
        double getHeight() const;

        void setLength(double length);
        void setWidth(double width);
        void setHeight(double height);

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        double _length;
        double _width;
        double _height;

        Math::hitdata_t calculateRectangleIntersection(const Math::Ray &localRay) const;
};

}  // namespace RayTracer::primitive

#endif //RAYTRACER_RECTANGLE_HPP
