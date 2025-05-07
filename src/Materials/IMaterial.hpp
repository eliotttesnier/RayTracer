/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include <memory>
#include <vector>

#include "../Lights/ILight.hpp"
#include "../Graphic/Color.hpp"
#include "../Math/HitData.hpp"
#include "../Math/Ray.hpp"

class IPrimitive;

namespace RayTracer::Materials {

class IMaterial {
    public:
        IMaterial() = default;
        virtual ~IMaterial() = default;

        virtual Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) = 0;
    };

};
    
#endif /* !IMATERIAL_HPP_ */
