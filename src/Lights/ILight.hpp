/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include <vector>
#include <memory>

#include "../Math/HitData.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Point3D.hpp"
#include "../Graphic/Color.hpp"
#include "../Primitives/IPrimitive.hpp"

class IPrimitive;

class ILight {
    public:
        virtual ~ILight() = default;

        // Basic light properties setters
        virtual void setPosition(float x, float y, float z) = 0;
        virtual void setColor(float r, float g, float b) = 0;
        virtual void setIntensity(float intensity) = 0;
        virtual void setDirection(const Math::Vector3D &direction) = 0;

        // Basic light properties getters
        virtual void getPosition(float &x, float &y, float &z) const = 0;
        virtual void getColor(float &r, float &g, float &b) const = 0;
        virtual void getIntensity(float &intensity) const = 0;
        virtual std::string getLightName() const = 0;
        virtual Math::Vector3D getDirection() const = 0;
        virtual std::string getType() = 0;

        // Check if this light illuminates the hit point (visibility test)
        virtual bool intersect(
            const Math::Ray &ray,
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) const = 0;

        // Helper method to check if point is in shadow
        virtual bool isInShadow(
            const Math::Point3D& hitPoint,
            const Math::Vector3D& lightDir,
            const std::vector<std::shared_ptr<IPrimitive>>& primitives
        ) const = 0;
};

#endif /* !ILIGHT_HPP_ */
