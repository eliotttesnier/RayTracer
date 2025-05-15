#ifndef RAYTRACER_GPU_RENDERER_HPP
#define RAYTRACER_GPU_RENDERER_HPP

#include "../Core/Renderer.hpp"
#include "CUDAStructures.cuh"
#include "CUDAKernel.cuh"

namespace RayTracer {

class GPURenderer {
private:
    Renderer& _cpuRenderer;
    bool _isInitialized;
    std::vector<CUDA::Sphere> _spheres;
    std::vector<CUDA::Triangle> _triangles;
    std::vector<CUDA::Light> _lights;
    CUDA::Camera _camera;
    CUDA::RenderParams _renderParams;
    std::vector<CUDA::Color> _outputBuffer;

public:
    GPURenderer(Renderer& cpuRenderer);
    ~GPURenderer();

    void initialize();
    void render();
    void saveToPPM(const std::string& filename) const;

private:
    void convertPrimitives();
    void convertLights();
    void convertCamera();
    void setupRenderParams();
};

} // namespace RayTracer

#endif // RAYTRACER_GPU_RENDERER_HPP
