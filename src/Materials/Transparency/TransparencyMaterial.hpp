/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** TransparencyMaterial
*/

#ifndef TRANSPARENCYMATERIAL_HPP_
#define TRANSPARENCYMATERIAL_HPP_

#include <memory>

#include "../../Primitives/Cone/Cone.hpp"
#include "../../Primitives/Cylinder/Cylinder.hpp"
#include "../../Primitives/Plane/Plane.hpp"
#include "../../Primitives/Sphere/Sphere.hpp"
#include "../../Primitives/Torus/Torus.hpp"
#include "../../Primitives/Tanglecube/Tanglecube.hpp"
#include "../../Primitives/Triangles/Triangles.hpp"
#include "../../Primitives/OBJ/OBJ.hpp"
#include "../../Primitives/FractaleCube/FractaleCube.hpp"
#include "../../Primitives/InfiniteCone/InfiniteCone.hpp"
#include "../../Primitives/InfiniteCylinder/InfiniteCylinder.hpp"
#include "../../Primitives/Rectangle/Rectangle.hpp"

#include "../AMaterial.hpp"

namespace RayTracer::Materials {

class TransparencyMaterial : public AMaterial {
    public:
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Cone &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Cylinder &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Plane &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Sphere &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Torus &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Tanglecube &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Triangles &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::OBJ &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::FractaleCube &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::InfiniteCone &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::InfiniteCylinder &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;
        Graphic::color_t calculateColor(
            const RayTracer::primitive::Rectangle &obj,
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

        TransparencyMaterial() = delete;
        TransparencyMaterial(std::shared_ptr<IMaterial> wrappee, double transparency);
        virtual ~TransparencyMaterial();

    private:
        std::shared_ptr<IMaterial> _wrappee;
        double _transparency;
        Graphic::color_t _calculateRatioColor(
            Graphic::color_t origin,
            Graphic::color_t behind
        );
        Graphic::color_t _getBehindColor(
            const Math::Ray &ray,
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives,
            std::vector<std::shared_ptr<ILight>> lights
        );
};

}

#endif /* !TRANSPARENCYMATERIAL_HPP_ */
