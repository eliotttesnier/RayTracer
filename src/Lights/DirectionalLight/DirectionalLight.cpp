//
// Created by roussierenoa on 4/28/25.
//

#include "DirectionalLight.hpp"
#include <iostream>
#include <cmath>

namespace RayTracer::light {
    DirectionalLight::DirectionalLight(const Math::Vector3D &direction)
        : _direction(direction)
    {
        this->_lightName = "DirectionalLight";
    }

    void DirectionalLight::setDirection(const Math::Vector3D &direction)
    {
        _direction = direction;
    }

    Math::Vector3D DirectionalLight::getDirection() const
    {
        return _direction;
    }

    bool DirectionalLight::intersect(
        const Math::Ray &ray,
        const Math::Point3D &hitPoint,
        std::vector<std::shared_ptr<IPrimitive>> primitives
    ) const
    {
        Math::Vector3D lightDir = -_direction.normalized();
        return !isInShadow(hitPoint, lightDir, primitives);
    }
    
    Graphic::color_t DirectionalLight::calculateLighting(
        const Math::hitdata_t& hitData,
        const Math::Ray& ray,
        const Math::Vector3D& viewDir
    ) const 
    {
        const float diffuseStrength = 0.7f;
        const float specularStrength = 0.3f;
        const int specularShininess = 32;
        
        Graphic::color_t baseColor = hitData.color;
        Graphic::color_t lightContribution = {0.0, 0.0, 0.0, baseColor.a};

        Math::Vector3D normal = hitData.normal.normalized();
        Math::Vector3D lightDir = -_direction.normalized();

        float diffuseFactor = std::max(0.0f, static_cast<float>(normal.dot(lightDir)));
        diffuseFactor = diffuseStrength * diffuseFactor * _intensity;

        Math::Vector3D halfwayDir = (lightDir + viewDir).normalized();
        float specularFactor = std::max(0.0f, static_cast<float>(normal.dot(halfwayDir)));
        specularFactor = pow(specularFactor, specularShininess) * specularStrength * _intensity;

        // Add diffuse contribution
        lightContribution.r += baseColor.r * diffuseFactor * _r;
        lightContribution.g += baseColor.g * diffuseFactor * _g;
        lightContribution.b += baseColor.b * diffuseFactor * _b;

        // Add specular contribution (white highlights)
        lightContribution.r += 255.0 * specularFactor;
        lightContribution.g += 255.0 * specularFactor;
        lightContribution.b += 255.0 * specularFactor;
        
        return lightContribution;
    }
}
