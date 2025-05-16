/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** RefractionMaterial
*/

#ifndef REFRACTIONMATERIAL_HPP_
#define REFRACTIONMATERIAL_HPP_

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

class RefractionMaterial : public AMaterial {
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

        RefractionMaterial() = delete;
        RefractionMaterial(std::shared_ptr<IMaterial> wrappee, double refraction);
        virtual ~RefractionMaterial();

    private:
        std::shared_ptr<IMaterial> _wrappee;
        double _refraction;
        double _ior;

        Graphic::color_t _calculateRefractionColor(
            const Math::Ray &ray,
            const Math::Point3D &hitPoint,
            const Math::Vector3D &normal,
            bool insideObject,
            std::vector<std::shared_ptr<IPrimitive>> primitives,
            std::vector<std::shared_ptr<ILight>> lights
        );
        Graphic::color_t _blendColors(
            Graphic::color_t originColor,
            Graphic::color_t refractionColor
        );
};

}

#endif /* !REFRACTIONMATERIAL_HPP_ */

