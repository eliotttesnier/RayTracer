/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include <string>
#include <vector>
#include <memory>

#include "../Lights/ILight.hpp"
#include "../Math/HitData.hpp"
#include "../Math/Ray.hpp"
#include "../Graphic/Color.hpp"

class ILight;
class IPrimitive;

class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        // Getters
        virtual std::string &getName() = 0;
        virtual std::string &getType() = 0;
        virtual Math::Point3D &getPosition() = 0;
        virtual Math::Vector3D &getRotation() = 0;

        // Methods
        virtual Math::hitdata_t intersect(const Math::Ray &ray) = 0;
        virtual Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) = 0;
};

#endif /* !IPRIMITIVE_HPP_ */
