/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** PerlinNoiseMaterial
*/

#ifndef PERLINNOISEMATERIAL_HPP_
#define PERLINNOISEMATERIAL_HPP_

#include "../AMaterial.hpp"
#include "../../Primitives/Rectangle/Rectangle.hpp"

namespace RayTracer::Materials
{

class PerlinNoiseMaterial : public AMaterial {
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

        PerlinNoiseMaterial() = delete;
        PerlinNoiseMaterial(std::shared_ptr<IMaterial> wrappee);
        virtual ~PerlinNoiseMaterial();

        private:
            std::shared_ptr<IMaterial> _wrappee;
            double _noise3d(double x, double y, double z);
            double _fade(double t);
            double _lerp(double a, double b, double t);
            Math::Vector3D _getConstantVector(int v);
            std::vector<int> _perm;
};

}

#endif /* !PERLINNOISEMATERIAL_HPP_ */
