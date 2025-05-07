/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** AMaterial
*/

#ifndef AMATERIAL_HPP_
#define AMATERIAL_HPP_

#include <cmath>

#include "IMaterial.hpp"

namespace RayTracer::Materials
{

class AMaterial : public IMaterial {
    protected:
        std::shared_ptr<IMaterial> _wrappee;

    public:
        AMaterial();
        AMaterial(std::shared_ptr<IMaterial> wrappee);
        virtual ~AMaterial() = default;

        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
};

}

#endif /* !AMATERIAL_HPP_ */
