#ifndef RAYTRACER_CUDA_KERNEL_CUH
#define RAYTRACER_CUDA_KERNEL_CUH

#include "CUDAStructures.cuh"
#include <cuda_runtime.h>

namespace RayTracer {
namespace CUDA {

/**
 * Convertit les structures C++ en structures CUDA
 */
void convertToCUDAStructures(
    const std::vector<std::shared_ptr<IPrimitive>>& primitives,
    const std::vector<std::shared_ptr<ILight>>& lights,
    const std::shared_ptr<RayTracer::Camera>& camera,
    const int width, const int height,
    std::vector<Sphere>& spheres,
    std::vector<Triangle>& triangles,
    std::vector<Light>& cudaLights,
    Camera& cudaCamera
);

/**
 * Initialise les structures de données sur le GPU
 */
void initGPUData(
    const std::vector<Sphere>& spheres,
    const std::vector<Triangle>& triangles,
    const std::vector<Light>& lights,
    const Camera& camera,
    const RenderParams& params
);

/**
 * Libère la mémoire GPU
 */
void freeGPUData();

/**
 * Lance le rendu CUDA
 */
void renderCUDA(Color* outputBuffer, int width, int height);

/**
 * Kernel principal pour le rendu
 */
__global__ void renderKernel(
    Color* outputBuffer,
    int width, int height,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles,
    Light* lights, int numLights,
    Camera camera,
    RenderParams params
);

/**
 * Trace un rayon sur le GPU
 */
__device__ HitData traceRay(
    const Ray& ray,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles,
    int depth
);

/**
 * Calcule la couleur pour un point d'intersection
 */
__device__ Color calculateColor(
    const HitData& hitData,
    const Ray& ray,
    Light* lights, int numLights,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles,
    int depth, int maxDepth
);

/**
 * Vérifie si un point est dans l'ombre
 */
__device__ bool isInShadow(
    const Point3D& hitPoint,
    const Vector3D& lightDir,
    float lightDistance,
    Sphere* spheres, int numSpheres,
    Triangle* triangles, int numTriangles
);

} // namespace CUDA
} // namespace RayTracer

#endif // RAYTRACER_CUDA_KERNEL_CUH
