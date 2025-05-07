/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP_
#define APRIMITIVE_HPP_

#include <cmath>

#include "IPrimitive.hpp"

class APrimitive : public IPrimitive {
    protected:
        std::string _name;
        std::string _type;
        Math::Point3D _position;
        Math::Vector3D _rotation;

    public:
        virtual ~APrimitive() = default;

        // Getters
        const std::string getName() const override;
        const std::string getType() const override;
        const Math::Point3D getPosition() const override;
        const Math::Vector3D getRotation() const override;

        // Setters
        void setName(const std::string &name) override;
        void setType(const std::string &type) override;
        void setPosition(const Math::Point3D &position) override;
        void setRotation(const Math::Vector3D &rotation) override;

        // Methods
        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
};

#endif /* !APRIMITIVE_HPP_ */
