/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <thread>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "../Lights/AmbientLight/AmbientLight.hpp"
#include "../Lights/DirectionalLight/DirectionalLight.hpp"

Renderer::Renderer(const std::shared_ptr<RayTracer::Camera> camera,
    const std::vector<std::shared_ptr<IPrimitive>> primitives,
    const std::vector<std::shared_ptr<ILight>> lights)
    : _camera(camera), _primitives(primitives), _lights(lights), _outputFile("output.ppm")
{
    _width = 1920;
    _height = 1080;
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
}

Renderer::~Renderer()
{
}

void Renderer::setCamera(const std::shared_ptr<RayTracer::Camera> camera)
{
    _camera = camera;
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
}

void Renderer::setPrimitives(const std::vector<std::shared_ptr<IPrimitive>>& primitives)
{
    _primitives = primitives;
}

void Renderer::setResolution(int width, int height)
{
    _width = width;
    _height = height;
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
}

void Renderer::setOutputFile(const std::string& outputFile)
{
    _outputFile = outputFile;
}

void Renderer::renderSegment(int startY, int endY)
{
    std::vector<std::vector<Graphic::color_t>> localBuffer(endY - startY,
            std::vector<Graphic::color_t>(_width));

    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < _width; x++) {
            double u = static_cast<double>(x) / (_width - 1);
            double v = static_cast<double>(y) / (_height - 1);

            u = u * 2.0 - 1.0;
            v = 1.0 - v * 2.0;
            u *= _aspectRatio;

            Math::Ray ray = _camera->ray(u, v);

            double closestDist = std::numeric_limits<double>::max();
            bool hit = false;
            Graphic::color_t pixelColor = {0.0, 0.0, 0.0, 1.0};
            Math::hitdata_t closestHitData;

            for (const auto& primitive : _primitives) {
                Math::hitdata_t hitData = primitive->intersect(ray);

                if (hitData.hit && hitData.distance < closestDist) {
                    closestDist = hitData.distance;
                    closestHitData = hitData;
                    hit = true;
                }
            }

            if (hit) {
                pixelColor = calculateLighting(closestHitData, ray);
            }

            localBuffer[y - startY][x] = pixelColor;
        }
    }

    std::lock_guard<std::mutex> lock(_mutex);
    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < _width; x++) {
            _pixelBuffer[y][x] = localBuffer[y - startY][x];
        }
    }
}

void Renderer::render()
{
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
    for (int y = 0; y < _height; y++) {
        _pixelBuffer[y].resize(_width);
    }

    unsigned int numThreads = std::min(std::thread::hardware_concurrency(), 1u);
    std::vector<std::thread> threads;
    const int linesPerThread = _height / numThreads;

    try {
        for (unsigned int i = 0; i < numThreads; i++) {
            int startY = i * linesPerThread;
            int endY = (i == numThreads - 1) ? _height : (i + 1) * linesPerThread;
            threads.emplace_back(&Renderer::renderSegment, this, startY, endY);
        }

        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    } catch (const std::exception& e) {
        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        throw;
    }

    saveToFile();
}

void Renderer::saveToFile()
{
    std::ofstream file(_outputFile);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + _outputFile);
    }

    file << "P3\n" << _width << " " << _height << "\n255\n";

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            const Graphic::color_t& color = _pixelBuffer[y][x];
            int r = static_cast<int>(std::round(std::max(0.0, std::min(255.0, color.r))));
            int g = static_cast<int>(std::round(std::max(0.0, std::min(255.0, color.g))));
            int b = static_cast<int>(std::round(std::max(0.0, std::min(255.0, color.b))));

            file << r << " " << g << " " << b << "\n";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Rendering complete. Output saved to " << _outputFile << std::endl;
}

Graphic::color_t Renderer::calculateLighting(const Math::hitdata_t& hitData, const Math::Ray& ray)
{
    if (_lights.empty()) {
        return hitData.color; // Return base color if no lights are present
    }

    // Improved lighting parameters for better shading
    const float ambientStrength = 0.3f;       // Base ambient lighting
    const float diffuseStrength = 0.7f;       // Diffuse lighting strength
    const float specularStrength = 0.2f;      // Specular highlight strength
    const int specularShininess = 32;         // Specular highlight sharpness

    // Get the base color from the hit data
    Graphic::color_t baseColor = hitData.color;
    Graphic::color_t finalColor = {0.0, 0.0, 0.0, baseColor.a};
    
    // Calculate view direction for specular lighting
    Math::Vector3D viewDir = -ray.direction.normalized();
    Math::Vector3D normal = hitData.normal.normalized();
    Math::Point3D hitPoint = hitData.point;
    
    // Start with a small ambient base to ensure nothing is completely black
    float ambientBase = 0.1f;
    finalColor.r += baseColor.r * ambientBase;
    finalColor.g += baseColor.g * ambientBase;
    finalColor.b += baseColor.b * ambientBase;

    // Track if we have ambient lights
    bool hasAmbientLight = false;

    // Process each light
    for (const auto& light : _lights) {
        std::string lightType = light->getType();
        
        // Handle ambient light differently
        if (lightType == "AmbientLight") {
            hasAmbientLight = true;
            float r, g, b, intensity;
            
            light->getColor(r, g, b);
            light->getIntensity(intensity);
            
            // Apply ambient light to the entire scene
            float ambientFactor = ambientStrength * intensity;
            finalColor.r += baseColor.r * ambientFactor * r;
            finalColor.g += baseColor.g * ambientFactor * g;
            finalColor.b += baseColor.b * ambientFactor * b;
            
            continue; // Skip the rest of the calculation for ambient lights
        }
        
        // For directional and other lights, check if they illuminate this point
        if (light->intersect(ray, hitPoint, _primitives)) {
            float r, g, b, intensity;
            float lightX, lightY, lightZ;
            
            // Get light properties
            light->getColor(r, g, b);
            light->getIntensity(intensity);
            light->getPosition(lightX, lightY, lightZ);
            
            Math::Vector3D lightDir;
            
            // For directional lights, use a hardcoded direction instead of dynamic_pointer_cast
            if (lightType == "DirectionalLight") {
                // Get light direction without using dynamic_cast to avoid linking errors
                // We'll use the light's position as a directional vector instead
                light->getPosition(lightX, lightY, lightZ);
                lightDir = Math::Vector3D(lightX, lightY, lightZ).normalized();
                // Negate the direction because directional lights shine from direction to point
                lightDir = Math::Vector3D(-lightDir._x, -lightDir._y, -lightDir._z);
            } else {
                // For point lights and other types, calculate direction from light to hit point
                lightDir = Math::Vector3D(
                    lightX - hitPoint._x,
                    lightY - hitPoint._y,
                    lightZ - hitPoint._z
                ).normalized();
            }
            
            // Calculate diffuse lighting with smoother falloff
            float diffuseFactor = std::max(0.0f, static_cast<float>(normal.dot(lightDir)));
            diffuseFactor = pow(diffuseFactor, 0.9f) * diffuseStrength * intensity;
            
            // Calculate specular lighting (Blinn-Phong model)
            Math::Vector3D halfwayDir = (lightDir + viewDir).normalized();
            float specularFactor = std::max(0.0f, static_cast<float>(normal.dot(halfwayDir)));
            specularFactor = pow(specularFactor, specularShininess) * specularStrength * intensity;
            
            // Add diffuse component
            finalColor.r += baseColor.r * diffuseFactor * r;
            finalColor.g += baseColor.g * diffuseFactor * g;
            finalColor.b += baseColor.b * diffuseFactor * b;
            
            // Add specular component (white highlight)
            float specularWhite = 255.0 * specularFactor;
            finalColor.r += specularWhite;
            finalColor.g += specularWhite;
            finalColor.b += specularWhite;
        } else if (lightType != "AmbientLight") {
            // For shadowed areas with non-ambient lights, add a small amount of light
            // to soften the shadows
            float r, g, b, intensity;
            light->getColor(r, g, b);
            light->getIntensity(intensity);
            
            float shadowAmbientFactor = 0.1f * intensity;
            finalColor.r += baseColor.r * shadowAmbientFactor * r;
            finalColor.g += baseColor.g * shadowAmbientFactor * g;
            finalColor.b += baseColor.b * shadowAmbientFactor * b;
        }
    }
    
    // If no ambient light was found, ensure minimal lighting
    if (!hasAmbientLight) {
        float minAmbient = 0.2f;
        finalColor.r = std::max(finalColor.r, baseColor.r * minAmbient);
        finalColor.g = std::max(finalColor.g, baseColor.g * minAmbient);
        finalColor.b = std::max(finalColor.b, baseColor.b * minAmbient);
    }
    
    // Apply a slight gamma correction for more natural lighting (gamma ≈ 2.2)
    finalColor.r = std::pow(finalColor.r / 255.0, 1.0 / 2.2) * 255.0;
    finalColor.g = std::pow(finalColor.g / 255.0, 1.0 / 2.2) * 255.0;
    finalColor.b = std::pow(finalColor.b / 255.0, 1.0 / 2.2) * 255.0;

    // Clamp color values
    finalColor.r = std::max(0.0, std::min(255.0, finalColor.r));
    finalColor.g = std::max(0.0, std::min(255.0, finalColor.g));
    finalColor.b = std::max(0.0, std::min(255.0, finalColor.b));

    return finalColor;
}
