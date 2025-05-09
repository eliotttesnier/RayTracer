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
        Graphic::color_t _getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        );

    public:
        AMaterial();
        AMaterial(std::shared_ptr<IMaterial> wrappee);
        virtual ~AMaterial() = default;

        Graphic::color_t calculateColor(
            RayTracer::primitive::Cone obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::Cylinder obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::Plane obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::Sphere obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::Torus obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::Tanglecube obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::Triangles obj,
            infos_t infos
        ) override;
        Graphic::color_t calculateColor(
            RayTracer::primitive::OBJ obj,
            infos_t infos
        ) override;
};

}

#endif /* !AMATERIAL_HPP_ */
