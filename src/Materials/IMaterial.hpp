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

#include "../Primitives/Cone/Cone.hpp"
#include "../Primitives/Cylinder/Cylinder.hpp"
#include "../Primitives/Plane/Plane.hpp"
#include "../Primitives/Sphere/Sphere.hpp"
#include "../Primitives/Torus/Torus.hpp"
#include "../Primitives/Tanglecube/Tanglecube.hpp"
#include "../Primitives/Triangles/Triangles.hpp"
#include "../Primitives/OBJ/OBJ.hpp"

class IPrimitive;

namespace RayTracer::Materials {

typedef struct infos_s {
    Math::hitdata_t hitData;
    Math::Ray ray;
    std::vector<std::shared_ptr<ILight>> lights;
    std::vector<std::shared_ptr<IPrimitive>> primitives;
} infos_t;

class IMaterial {
    public:
        IMaterial() = default;
        virtual ~IMaterial() = default;

        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Cone obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Cylinder obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Plane obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Sphere obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Torus obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Tanglecube obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::Triangles obj,
            infos_t infos
        ) = 0;
        virtual Graphic::color_t calculateColor(
            RayTracer::primitive::OBJ obj,
            infos_t infos
        ) = 0;
};

};
    
#endif /* !IMATERIAL_HPP_ */
