//
// Created by roussierenoa on 4/28/25.
//

#ifndef PLANE_HPP
#define PLANE_HPP

#include "../APrimitive.hpp"
#include "../../Math/Rectangle3D.hpp"

namespace RayTracer::primitive {

class Plane : public APrimitive {
    public:
        Plane();
        Plane(const Math::Point3D &position, const Math::Vector3D &rotation);
        ~Plane() = default;

        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

        double getWidth() const;
        void setWidth(double width);
        double getHeight() const;
        void setHeight(double height);

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

    private:
        RayTracer::Rectangle3D _rectangle;
};

} // Raytracer

#endif //PLANE_HPP
