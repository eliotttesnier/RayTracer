/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** NormalMappingMaterial
*/

#ifndef NORMALMAPPINGMATERIAL_HPP_
#define NORMALMAPPINGMATERIAL_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <tuple>
#include <string>

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

class NormalMappingMaterial : public AMaterial {
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

        NormalMappingMaterial();
        NormalMappingMaterial(std::shared_ptr<IMaterial> wrappee, std::string normalMapPath);
        virtual ~NormalMappingMaterial();

        void setNormalMapIntensity(float intensity) { _normalMapIntensity = intensity; }

    private:
        std::shared_ptr<IMaterial> _wrappee;
        std::string _normalMapPath;
        sf::Image _normalMapImage;
        sf::Vector2u _normalMapSize;
        bool _normalMapLoaded = false;
        float _normalMapIntensity = 1.0f;

        Math::Vector3D getNormalFromMap(float u, float v) const;

        Math::Vector3D transformNormal(
            const Math::Vector3D &normal,
            const Math::Vector3D &surfaceNormal,
            const Math::Point3D &hitPoint,
            float u, float v
        ) const;

        std::tuple<Math::Vector3D, Math::Vector3D> createTangentSpace(
            const Math::Vector3D &normal
        ) const;
};

}

#endif /* !NORMALMAPPINGMATERIAL_HPP_ */
