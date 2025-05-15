#include "GPURenderer.hpp"
#include <fstream>
#include <iostream>

namespace RayTracer {

GPURenderer::GPURenderer(Renderer& cpuRenderer)
    : _cpuRenderer(cpuRenderer), _isInitialized(false)
{
}

GPURenderer::~GPURenderer()
{
    // Libérer les ressources GPU
    if (_isInitialized) {
        CUDA::freeGPUData();
    }
}

void GPURenderer::initialize()
{
    // Convertir les données CPU en structures compatibles GPU
    convertPrimitives();
    convertLights();
    convertCamera();
    setupRenderParams();
    
    // Initialiser les données sur le GPU
    CUDA::initGPUData(_spheres, _triangles, _lights, _camera, _renderParams);
    
    _isInitialized = true;
    
    // Préparer le buffer de sortie
    _outputBuffer.resize(_renderParams.width * _renderParams.height);
}

void GPURenderer::render()
{
    if (!_isInitialized) {
        initialize();
    }
    
    // Lancer le rendu sur le GPU
    CUDA::renderCUDA(_outputBuffer.data(), _renderParams.width, _renderParams.height);
    
    // Mettre à jour le buffer CPU du renderer
    // Vous devrez ajouter une méthode d'accès au buffer dans la classe Renderer
    for (int y = 0; y < _renderParams.height; y++) {
        for (int x = 0; x < _renderParams.width; x++) {
            int index = y * _renderParams.width + x;
            Graphic::color_t color = {
                _outputBuffer[index].r,
                _outputBuffer[index].g,
                _outputBuffer[index].b,
                _outputBuffer[index].a
            };
            // Mise à jour du buffer du renderer CPU (à implémenter dans Renderer)
            // _cpuRenderer.setPixelColor(x, y, color);
        }
    }
}

void GPURenderer::saveToPPM(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }
    
    // Écrire l'en-tête PPM
    file << "P3\n" << _renderParams.width << " " << _renderParams.height << "\n255\n";
    
    // Écrire les données des pixels
    for (int y = 0; y < _renderParams.height; y++) {
        for (int x = 0; x < _renderParams.width; x++) {
            int index = y * _renderParams.width + x;
            int r = static_cast<int>(_outputBuffer[index].r);
            int g = static_cast<int>(_outputBuffer[index].g);
            int b = static_cast<int>(_outputBuffer[index].b);
            
            // Limiter les valeurs à l'intervalle [0, 255]
            r = std::max(0, std::min(255, r));
            g = std::max(0, std::min(255, g));
            b = std::max(0, std::min(255, b));
            
            file << r << " " << g << " " << b << "\n";
        }
    }
    
    file.close();
}

void GPURenderer::convertPrimitives()
{
    // Récupérer les primitives du renderer CPU
    auto primitives = _cpuRenderer.getPrimitives();
    
    // Convertir les primitives en structures GPU
    CUDA::convertToCUDAStructures(
        primitives,
        _cpuRenderer.getLights(),
        _cpuRenderer.getCamera(),
        _cpuRenderer.getWidth(),
        _cpuRenderer.getHeight(),
        _spheres,
        _triangles,
        _lights,
        _camera
    );
}

void GPURenderer::convertLights()
{
    // Cette conversion est déjà effectuée dans convertToCUDAStructures
}

void GPURenderer::convertCamera()
{
    // Cette conversion est déjà effectuée dans convertToCUDAStructures
}

void GPURenderer::setupRenderParams()
{
    _renderParams.width = _cpuRenderer.getWidth();
    _renderParams.height = _cpuRenderer.getHeight();
    _renderParams.maxDepth = 5;  // Profondeur maximale de récursion
    
    // Récupérer les paramètres d'antialiasing
    auto antialiasingMode = _cpuRenderer.getAntialiasingMode();
    _renderParams.useAntialiasing = (antialiasingMode != Renderer::NONE);
    _renderParams.samples = _cpuRenderer.getSupersamplingLevel();
}

} // namespace RayTracer
