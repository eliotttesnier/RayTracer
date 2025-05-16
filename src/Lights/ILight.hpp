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

typedef struct lightInfos_s {
    bool hit;
    Math::Vector3D lightDir;
} lightInfos_t;

class ILight {
    public:
        virtual ~ILight() = default;

        // Basic light properties setters
        virtual void setPosition(const Math::Point3D &pos) = 0;
        virtual void setColor(int r, int g, int b) = 0;
        virtual void setIntensity(float intensity) = 0;
        virtual void setDirection(const Math::Vector3D &direction) = 0;

        // Basic light properties getters
        virtual Math::Point3D getPosition() const = 0;
        virtual std::tuple<int, int, int> getColor() const = 0;
        virtual float getIntensity() const = 0;
        virtual std::string getLightName() const = 0;
        virtual Math::Vector3D getDirection() const = 0;
        virtual std::string getType() = 0;

        // Check if this light illuminates the hit point (visibility test)
        virtual lightInfos_t intersect(
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) const = 0;

        // Helper method to check if point is in shadow
        virtual bool isInShadow(
            const Math::Point3D& hitPoint,
            const Math::Vector3D& lightDir,
            const std::vector<std::shared_ptr<IPrimitive>> &primitives
        ) const = 0;
};

#endif /* !ILIGHT_HPP_ */
