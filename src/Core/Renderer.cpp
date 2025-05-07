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
#include <memory>
#include <thread>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include "../Lights/AmbientLight/AmbientLight.hpp"
#include "../Lights/DirectionalLight/DirectionalLight.hpp"

Renderer::Renderer(const std::shared_ptr<RayTracer::Camera> camera,
    const std::vector<std::shared_ptr<IPrimitive>> primitives,
    const std::vector<std::shared_ptr<ILight>> lights)
    : _camera(camera), _primitives(primitives), _lights(lights), _outputFile("output.ppm")
{
    _width = std::get<0>(camera->getResolution());
    _height = std::get<1>(camera->getResolution());
    _aspectRatio = static_cast<double>(_width) / _height;
    _fov = camera->getFov();
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

void Renderer::setLight(const std::vector<std::shared_ptr<ILight>>& lights) {
    _lights = lights;
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
            std::shared_ptr<IPrimitive> closestPrimitive;

            for (const auto& primitive : _primitives) {
                Math::hitdata_t hitData = primitive->intersect(ray);

                if (hitData.hit && hitData.distance < closestDist) {
                    closestDist = hitData.distance;
                    closestHitData = hitData;
                    closestPrimitive = primitive;
                    hit = true;
                }
            }

            if (hit) {
                pixelColor = closestPrimitive->getColor(closestHitData,
                                                        ray,
                                                        _lights,
                                                        _primitives);
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

    unsigned int numThreads = std::min(std::thread::hardware_concurrency(), 8u);
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
