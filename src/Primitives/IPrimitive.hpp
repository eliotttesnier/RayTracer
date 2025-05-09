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
        virtual const std::string getName() const = 0;
        virtual const std::string getType() const = 0;
        virtual const Math::Point3D getPosition() const = 0;
        virtual const Math::Vector3D getRotation() const = 0;
        virtual const Math::Vector3D getShear() const = 0;

        // Setters
        virtual void setName(const std::string &name) = 0;
        virtual void setType(const std::string &type) = 0;
        virtual void setPosition(const Math::Point3D &position) = 0;
        virtual void setRotation(const Math::Vector3D &rotation) = 0;
        virtual void setScale(const Math::Vector3D &scale) = 0;
        virtual void setShear(const Math::Vector3D &shear) = 0;
        virtual void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) = 0;

        // Methods
        virtual Math::hitdata_t intersect(const Math::Ray &ray) = 0;
        virtual Graphic::color_t getColor(
            RayTracer::Materials::infos_t infos
        ) = 0;
};

#endif /* !IPRIMITIVE_HPP_ */
