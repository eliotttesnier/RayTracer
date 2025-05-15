#include "CUDAKernel.cuh"
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdexcept>
#include "../Math/Point3D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/Ray.hpp"
#include "../Graphic/Color.hpp"
#include "../Primitives/Sphere/Sphere.hpp"
#include "../Primitives/Triangles/Triangles.hpp"
#include "../Lights/ILight.hpp"
#include "../Graphic/Camera.hpp"

namespace RayTracer {
namespace CUDA {

// Variables pour stocker les données sur le GPU
Sphere* d_spheres = nullptr;
Triangle* d_triangles = nullptr;
Light* d_lights = nullptr;
int numSpheres = 0;
int numTriangles = 0;
int numLights = 0;
RenderParams renderParams;

// Fonctions utilitaires pour le CUDA
__device__ float dot(const Vector3D& a, const Vector3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

__device__ float length(const Vector3D& v) {
    return sqrtf(dot(v, v));
}

__device__ Vector3D normalize(const Vector3D& v) {
    float len = length(v);
    if (len > 0.0f) {
        return {v.x / len, v.y / len, v.z / len};
    }
    return v;
}

__device__ Vector3D cross(const Vector3D& a, const Vector3D& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

__device__ Vector3D subtract(const Point3D& a, const Point3D& b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

__device__ Point3D add(const Point3D& p, const Vector3D& v) {
    return {p.x + v.x, p.y + v.y, p.z + v.z};
}

__device__ Ray generateRay(const Camera& camera, float u, float v) {
    // Calcul de la direction du rayon en fonction des coordonnées de l'écran
    float aspectRatio = camera.aspectRatio;
    float scale = tanf(camera.fov * 0.5f * 3.14159f / 180.0f);
    
    float imageX = (2.0f * u - 1.0f) * aspectRatio * scale;
    float imageY = (1.0f - 2.0f * v) * scale;
    
    Vector3D direction = {
        camera.right.x * imageX + camera.up.x * imageY + camera.direction.x,
        camera.right.y * imageX + camera.up.y * imageY + camera.direction.y,
        camera.right.z * imageX + camera.up.z * imageY + camera.direction.z
    };
    
    return {camera.position, normalize(direction)};
}

__device__ bool intersectSphere(const Ray& ray, const Sphere& sphere, HitData& hitData) {
    Vector3D oc = {
        ray.origin.x - sphere.center.x,
        ray.origin.y - sphere.center.y,
        ray.origin.z - sphere.center.z
    };
    
    float a = dot(ray.direction, ray.direction);
    float b = 2.0f * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return false;
    }
    
    float t = (-b - sqrtf(discriminant)) / (2.0f * a);
    if (t < 0.001f) {
        t = (-b + sqrtf(discriminant)) / (2.0f * a);
        if (t < 0.001f) {
            return false;
        }
    }
    
    hitData.distance = t;
    hitData.point = {
        ray.origin.x + ray.direction.x * t,
        ray.origin.y + ray.direction.y * t,
        ray.origin.z + ray.direction.z * t
    };
    
    Vector3D normal = {
        (hitData.point.x - sphere.center.x) / sphere.radius,
        (hitData.point.y - sphere.center.y) / sphere.radius,
        (hitData.point.z - sphere.center.z) / sphere.radius
    };
    
    hitData.normal = normalize(normal);
    hitData.color = sphere.color;
    hitData.hit = true;
    
    return true;
}

__device__ bool intersectTriangle(const Ray& ray, const Triangle& triangle, HitData& hitData) {
    // Implémentation de l'algorithme de Möller-Trumbore
    Vector3D edge1 = subtract(triangle.p2, triangle.p1);
    Vector3D edge2 = subtract(triangle.p3, triangle.p1);
    Vector3D h = cross(ray.direction, edge2);
    float a = dot(edge1, h);
    
    if (a > -0.0001f && a < 0.0001f) {
        return false; // Le rayon est parallèle au triangle
    }
    
    float f = 1.0f / a;
    Vector3D s = subtract(ray.origin, triangle.p1);
    float u = f * dot(s, h);
    
    if (u < 0.0f || u > 1.0f) {
        return false;
    }
    
    Vector3D q = cross(s, edge1);
    float v = f * dot(ray.direction, q);
    
    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }
    
    float t = f * dot(edge2, q);
    
    if (t > 0.001f) {
        hitData.distance = t;
        hitData.point = {
            ray.origin.x + ray.direction.x * t,
            ray.origin.y + ray.direction.y * t,
            ray.origin.z + ray.direction.z * t
        };
        
        hitData.normal = triangle.normal;
        hitData.color = triangle.color;
        hitData.hit = true;
        return true;
    }
    
    return false;
}

__device__ HitData traceRay(
    const Ray& ray,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles,
    int depth
) {
    HitData closestHit;
    closestHit.hit = false;
    closestHit.distance = FLT_MAX;
    
    // Vérifier l'intersection avec toutes les sphères
    for (int i = 0; i < numSpheres; i++) {
        HitData hitData;
        hitData.hit = false;
        
        if (intersectSphere(ray, spheres[i], hitData)) {
            if (hitData.distance < closestHit.distance) {
                closestHit = hitData;
            }
        }
    }
    
    // Vérifier l'intersection avec tous les triangles
    for (int i = 0; i < numTriangles; i++) {
        HitData hitData;
        hitData.hit = false;
        
        if (intersectTriangle(ray, triangles[i], hitData)) {
            if (hitData.distance < closestHit.distance) {
                closestHit = hitData;
            }
        }
    }
    
    return closestHit;
}

__device__ bool isInShadow(
    const Point3D& hitPoint,
    const Vector3D& lightDir,
    float lightDistance,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles
) {
    // Bias pour éviter les ombres acnéiques (shadow acne)
    const float SHADOW_BIAS = 0.001f;
    Point3D shadowOrigin = {
        hitPoint.x + lightDir.x * SHADOW_BIAS,
        hitPoint.y + lightDir.y * SHADOW_BIAS,
        hitPoint.z + lightDir.z * SHADOW_BIAS
    };
    
    Ray shadowRay = {shadowOrigin, lightDir};
    
    // Vérifier les intersections pour déterminer si le point est dans l'ombre
    for (int i = 0; i < numSpheres; i++) {
        HitData hitData;
        if (intersectSphere(shadowRay, spheres[i], hitData)) {
            if (hitData.distance > 0.0f && (lightDistance < 0.0f || hitData.distance < lightDistance)) {
                return true;
            }
        }
    }
    
    for (int i = 0; i < numTriangles; i++) {
        HitData hitData;
        if (intersectTriangle(shadowRay, triangles[i], hitData)) {
            if (hitData.distance > 0.0f && (lightDistance < 0.0f || hitData.distance < lightDistance)) {
                return true;
            }
        }
    }
    
    return false;
}

__device__ Color calculateColor(
    const HitData& hitData,
    const Ray& ray,
    Light* lights, int numLights,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles,
    int depth, int maxDepth
) {
    if (!hitData.hit || depth >= maxDepth) {
        return {0.0f, 0.0f, 0.0f, 1.0f};
    }
    
    Color finalColor = {0.0f, 0.0f, 0.0f, 1.0f};
    
    // Facteurs de phong
    const float ka = 0.1f;  // Ambient
    const float kd = 0.7f;  // Diffuse
    const float ks = 0.2f;  // Specular
    const float shininess = 32.0f;
    
    // Calculer la contribution de chaque lumière
    for (int i = 0; i < numLights; i++) {
        Light light = lights[i];
        
        // Lumière ambiante (toujours présente)
        if (light.type == 0) { // Ambient
            finalColor.r += light.color.r * light.intensity * ka;
            finalColor.g += light.color.g * light.intensity * ka;
            finalColor.b += light.color.b * light.intensity * ka;
            continue;
        }
        
        // Calculer la direction de la lumière
        Vector3D lightDir;
        float lightDistance = -1.0f;
        
        if (light.type == 1) { // Directional
            lightDir = {-light.direction.x, -light.direction.y, -light.direction.z};
        } else { // Point
            lightDir = {
                light.position.x - hitData.point.x,
                light.position.y - hitData.point.y,
                light.position.z - hitData.point.z
            };
            lightDistance = length(lightDir);
            lightDir = {
                lightDir.x / lightDistance,
                lightDir.y / lightDistance,
                lightDir.z / lightDistance
            };
        }
        
        // Vérifier si le point est dans l'ombre
        if (!isInShadow(hitData.point, lightDir, lightDistance, spheres, numSpheres, triangles, numTriangles)) {
            // Éclairage diffus
            float diffuse = max(0.0f, dot(hitData.normal, lightDir));
            
            // Éclairage spéculaire
            Vector3D reflectDir = {
                2.0f * dot(hitData.normal, lightDir) * hitData.normal.x - lightDir.x,
                2.0f * dot(hitData.normal, lightDir) * hitData.normal.y - lightDir.y,
                2.0f * dot(hitData.normal, lightDir) * hitData.normal.z - lightDir.z
            };
            Vector3D viewDir = {-ray.direction.x, -ray.direction.y, -ray.direction.z};
            float specular = powf(max(0.0f, dot(reflectDir, viewDir)), shininess);
            
            // Atténuation pour les lumières ponctuelles
            float attenuation = 1.0f;
            if (light.type == 2) { // Point
                attenuation = 1.0f / (1.0f + 0.09f * lightDistance + 0.032f * lightDistance * lightDistance);
            }
            
            // Ajouter la contribution de la lumière
            finalColor.r += (diffuse * kd + specular * ks) * light.color.r * light.intensity * attenuation;
            finalColor.g += (diffuse * kd + specular * ks) * light.color.g * light.intensity * attenuation;
            finalColor.b += (diffuse * kd + specular * ks) * light.color.b * light.intensity * attenuation;
        }
    }
    
    // Appliquer la couleur de l'objet
    finalColor.r *= hitData.color.r;
    finalColor.g *= hitData.color.g;
    finalColor.b *= hitData.color.b;
    
    // Correction gamma simple
    finalColor.r = min(1.0f, finalColor.r);
    finalColor.g = min(1.0f, finalColor.g);
    finalColor.b = min(1.0f, finalColor.b);
    
    // Conversion en espace RGB 0-255
    finalColor.r = powf(finalColor.r, 1.0f/2.2f) * 255.0f;
    finalColor.g = powf(finalColor.g, 1.0f/2.2f) * 255.0f;
    finalColor.b = powf(finalColor.b, 1.0f/2.2f) * 255.0f;
    
    return finalColor;
}

__global__ void renderKernel(
    Color* outputBuffer,
    int width, int height,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles,
    Light* lights, int numLights,
    Camera camera,
    RenderParams params
) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (x >= width || y >= height) {
        return;
    }
    
    int pixelIndex = y * width + x;
    
    // Calcul des coordonnées UV normalisées
    float u = (float)x / (float)(width - 1);
    float v = (float)y / (float)(height - 1);
    
    // Génération du rayon
    Ray ray = generateRay(camera, u, v);
    
    // Anti-aliasing par échantillonnage (supersampling)
    Color pixelColor = {0.0f, 0.0f, 0.0f, 1.0f};
    
    if (params.useAntialiasing) {
        for (int sy = 0; sy < params.samples; sy++) {
            for (int sx = 0; sx < params.samples; sx++) {
                float su = ((float)x + (sx + 0.5f) / params.samples) / (float)(width - 1);
                float sv = ((float)y + (sy + 0.5f) / params.samples) / (float)(height - 1);
                
                Ray sampleRay = generateRay(camera, su, sv);
                HitData hitData = traceRay(sampleRay, spheres, numSpheres, triangles, numTriangles, 0);
                
                Color sampleColor = calculateColor(
                    hitData, sampleRay, 
                    lights, numLights, 
                    spheres, numSpheres, 
                    triangles, numTriangles, 
                    0, params.maxDepth
                );
                
                pixelColor.r += sampleColor.r;
                pixelColor.g += sampleColor.g;
                pixelColor.b += sampleColor.b;
            }
        }
        
        float invSamples = 1.0f / (params.samples * params.samples);
        pixelColor.r *= invSamples;
        pixelColor.g *= invSamples;
        pixelColor.b *= invSamples;
    } else {
        // Sans anti-aliasing
        HitData hitData = traceRay(ray, spheres, numSpheres, triangles, numTriangles, 0);
        pixelColor = calculateColor(
            hitData, ray, 
            lights, numLights, 
            spheres, numSpheres, 
            triangles, numTriangles, 
            0, params.maxDepth
        );
    }
    
    // Écriture dans le buffer de sortie
    outputBuffer[pixelIndex] = pixelColor;
}

// Implémentation des fonctions d'interface avec le CPU
void convertToCUDAStructures(
    const std::vector<std::shared_ptr<IPrimitive>>& primitives,
    const std::vector<std::shared_ptr<ILight>>& lights,
    const std::shared_ptr<RayTracer::Camera>& camera,
    const int width, const int height,
    std::vector<Sphere>& spheres,
    std::vector<Triangle>& triangles,
    std::vector<Light>& cudaLights,
    Camera& cudaCamera
) {
    // Conversion des sphères
    for (const auto& primitive : primitives) {
        auto sphere = std::dynamic_pointer_cast<RayTracer::primitive::Sphere>(primitive);
        if (sphere) {
            Sphere cudaSphere;
            
            // Conversion de la position
            Math::Point3D pos = sphere->getPosition();
            cudaSphere.center = {static_cast<float>(pos._x), static_cast<float>(pos._y), static_cast<float>(pos._z)};
            
            // Conversion du rayon
            cudaSphere.radius = static_cast<float>(sphere->getRadius());
            
            // Conversion de la couleur
            Graphic::color_t color = sphere->getColor();
            cudaSphere.color = {static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a)};
            
            // Propriétés matérielles (simplifiées)
            cudaSphere.reflection = 0.0f;  // À compléter avec les vraies propriétés
            cudaSphere.refraction = 0.0f;
            cudaSphere.transparency = 0.0f;
            
            spheres.push_back(cudaSphere);
        }
        
        auto triangle = std::dynamic_pointer_cast<RayTracer::primitive::Triangles>(primitive);
        if (triangle) {
            Triangle cudaTriangle;
            
            // À compléter pour les triangles
            triangles.push_back(cudaTriangle);
        }
    }
    
    // Conversion des lumières
    for (const auto& light : lights) {
        Light cudaLight;
        
        // Position
        Math::Point3D pos = light->getPosition();
        cudaLight.position = {static_cast<float>(pos._x), static_cast<float>(pos._y), static_cast<float>(pos._z)};
        
        // Direction (pour les lumières directionnelles)
        Math::Vector3D dir = light->getDirection();
        cudaLight.direction = {static_cast<float>(dir._x), static_cast<float>(dir._y), static_cast<float>(dir._z)};
        
        // Couleur
        auto [r, g, b] = light->getColor();
        cudaLight.color = {static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f, 1.0f};
        
        // Intensité
        float intensity;
        light->getIntensity(intensity);
        cudaLight.intensity = intensity;
        
        // Type
        std::string type = light->getType();
        if (type == "AmbientLight") {
            cudaLight.type = 0;
        } else if (type == "DirectionalLight") {
            cudaLight.type = 1;
        } else if (type == "PositionLight" || type == "PointLight") {
            cudaLight.type = 2;  // Point light
        } else {
            cudaLight.type = 2;  // Point light par défaut
        }
        
        cudaLights.push_back(cudaLight);
    }
    
    // Conversion de la caméra
    Math::Point3D camPos = camera->getPosition();
    cudaCamera.position = {static_cast<float>(camPos._x), static_cast<float>(camPos._y), static_cast<float>(camPos._z)};
    
    cudaCamera.fov = static_cast<float>(camera->getFov());
    cudaCamera.aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    
    // Construction des vecteurs de base de la caméra
    Math::Vector3D camDirection = camera->getForward();
    Math::Vector3D camUp = camera->getUp();
    Math::Vector3D camRight = camera->getRight();
    
    cudaCamera.direction = {static_cast<float>(camDirection._x), static_cast<float>(camDirection._y), static_cast<float>(camDirection._z)};
    cudaCamera.up = {static_cast<float>(camUp._x), static_cast<float>(camUp._y), static_cast<float>(camUp._z)};
    cudaCamera.right = {static_cast<float>(camRight._x), static_cast<float>(camRight._y), static_cast<float>(camRight._z)};
}

void initGPUData(
    const std::vector<Sphere>& spheres,
    const std::vector<Triangle>& triangles,
    const std::vector<Light>& lights,
    const Camera& camera,
    const RenderParams& params
) {
    // Libérer d'abord la mémoire si nécessaire
    freeGPUData();
    
    // Stocker le nombre d'objets
    numSpheres = spheres.size();
    numTriangles = triangles.size();
    numLights = lights.size();
    renderParams = params;
    
    // Allouer et copier les données sur le GPU
    if (numSpheres > 0) {
        cudaMalloc(&d_spheres, numSpheres * sizeof(Sphere));
        cudaMemcpy(d_spheres, spheres.data(), numSpheres * sizeof(Sphere), cudaMemcpyHostToDevice);
    }
    
    if (numTriangles > 0) {
        cudaMalloc(&d_triangles, numTriangles * sizeof(Triangle));
        cudaMemcpy(d_triangles, triangles.data(), numTriangles * sizeof(Triangle), cudaMemcpyHostToDevice);
    }
    
    if (numLights > 0) {
        cudaMalloc(&d_lights, numLights * sizeof(Light));
        cudaMemcpy(d_lights, lights.data(), numLights * sizeof(Light), cudaMemcpyHostToDevice);
    }
}

void freeGPUData() {
    if (d_spheres) {
        cudaFree(d_spheres);
        d_spheres = nullptr;
    }
    
    if (d_triangles) {
        cudaFree(d_triangles);
        d_triangles = nullptr;
    }
    
    if (d_lights) {
        cudaFree(d_lights);
        d_lights = nullptr;
    }
}

void renderCUDA(Color* outputBuffer, int width, int height) {
    // Allouer le buffer de sortie sur le GPU
    Color* d_outputBuffer;
    cudaMalloc(&d_outputBuffer, width * height * sizeof(Color));
    
    // Configurer les dimensions des blocs et de la grille
    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y);
    
    // Lancer le kernel
    renderKernel<<<gridSize, blockSize>>>(
        d_outputBuffer,
        width, height,
        d_spheres, numSpheres,
        d_triangles, numTriangles,
        d_lights, numLights,
        Camera(),  // Cette caméra doit être initialisée correctement
        renderParams
    );
    
    // Attendre que tous les threads aient terminé
    cudaDeviceSynchronize();
    
    // Copier le résultat du GPU vers le CPU
    cudaMemcpy(outputBuffer, d_outputBuffer, width * height * sizeof(Color), cudaMemcpyDeviceToHost);
    
    // Libérer la mémoire
    cudaFree(d_outputBuffer);
}

} // namespace CUDA
} // namespace RayTracer
