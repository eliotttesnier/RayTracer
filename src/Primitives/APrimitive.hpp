/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP_
#define APRIMITIVE_HPP_

#include <cmath>
#include <limits>

#include "../Materials/IMaterial.hpp"
#include "IPrimitive.hpp"

namespace RayTracer::primitive {

class APrimitive : public IPrimitive {
    protected:
        std::string _name;
        Math::Point3D _position;
        Graphic::color_t _color;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        Math::Vector3D _anchorPoint;
        std::shared_ptr<RayTracer::Materials::IMaterial> _material;
        AABB _boundingBox;

    public:
        virtual ~APrimitive() = default;

        // Getters
        const std::string getName() const override;
        const Math::Point3D getPosition() const override;
        const Math::Vector3D getRotation() const override;
        const Math::Vector3D getShear() const override;
        const RayTracer::primitive::AABB getBoundingBox() const override;

        // Setters
        void setName(const std::string &name) override;
        void setPosition(const Math::Point3D &position) override;
        void setRotation(const Math::Vector3D &rotation) override;
        void setScale(const Math::Vector3D &scale) override;
        void setShear(const Math::Vector3D &shear) override;
        void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) override;
        void setColor(const Graphic::color_t &color) override;

        // Methods
        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

        Math::Ray transformRayToLocal(const Math::Ray &ray) const;
        Math::Point3D transformPointToLocal(const Math::Point3D &point) const;
        Math::Point3D transformPointToWorld(const Math::Point3D &localPoint) const;
        Math::Vector3D transformNormalToWorld(const Math::Vector3D &localNormal) const;

        void rotatePointToLocal(
            Math::Point3D &point,
            double cosX,
            double sinX,
            double cosY,
            double sinY,
            double cosZ,
            double sinZ
        ) const;
        void rotateVectorToLocal(
            Math::Vector3D &vector,
            double cosX,
            double sinX,
            double cosY,
            double sinY,
            double cosZ,
            double sinZ
        ) const;
        void rotatePointToWorld(
            Math::Point3D &point,
            double cosX,
            double sinX,
            double cosY,
            double sinY,
            double cosZ,
            double sinZ
        ) const;
        void rotateVectorToWorld(
            Math::Vector3D &vector,
            double cosX,
            double sinX,
            double cosY,
            double sinY,
            double cosZ,
            double sinZ
        ) const;
};

} // namespace RayTracer::primitive

#endif /* !APRIMITIVE_HPP_ */
