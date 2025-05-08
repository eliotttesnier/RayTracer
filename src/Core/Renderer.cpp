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
#include <iomanip>
#include <sstream>
#include "../Lights/AmbientLight/AmbientLight.hpp"
#include "../Lights/DirectionalLight/DirectionalLight.hpp"

Renderer::Renderer(const std::shared_ptr<RayTracer::Camera> camera,
    const std::vector<std::shared_ptr<IPrimitive>> primitives,
    const std::vector<std::shared_ptr<ILight>> lights)
    : _camera(camera), _primitives(primitives), _lights(lights),
    _outputFile("output.ppm"), _previewOutputFile("preview.ppm")
{
    _width = std::get<0>(camera->getResolution());
    _height = std::get<1>(camera->getResolution());
    _previewWidth = 256;
    _previewHeight = static_cast<int>(_previewWidth * (_height / static_cast<double>(_width)));
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
    _previewWidth = 256;
    _previewHeight = static_cast<int>(_previewWidth*(_height / static_cast<double>(_width)));
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
}

void Renderer::setOutputFile(const std::string& outputFile)
{
    _outputFile = outputFile;
}

std::string Renderer::formatTime(double seconds)
{
    int hours = static_cast<int>(seconds) / 3600;
    int minutes = (static_cast<int>(seconds) % 3600) / 60;
    int secs = static_cast<int>(seconds) % 60;

    std::stringstream ss;
    if (hours > 0)
        ss << hours << "h ";
    if (hours > 0 || minutes > 0)
        ss << minutes << "m ";
    ss << secs << "s";
    return ss.str();
}

void Renderer::updateProgress()
{
    int completed = _completedLines.load();
    int percentage = (completed * 100) / _height;

    std::cout << "\rRendering: [";
    int barWidth = 50;
    int pos = barWidth * percentage / 100;

    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }

    std::cout << "] " << std::setw(3) << percentage << "%";
    if (completed > 0 && _pixelsPerSecond > 0) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - _startTime;
        double remainingLines = _height - completed;
        double remainingPixels = remainingLines * _width;
        double estimatedRemainingSeconds = remainingPixels / _pixelsPerSecond;
        std::cout << " | Est. remaining: " << formatTime(estimatedRemainingSeconds)
            << "                     ";
    }
    std::cout << std::flush;
}

void Renderer::renderSegment(int startY, int endY)
{
    std::vector<std::vector<Graphic::color_t>> localBuffer(endY - startY,
        std::vector<Graphic::color_t>(_width));

    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < _width; x++) {
            double u = (2.0 * static_cast<double>(x) / (_width - 1)) - 1.0;
            double v = 1.0 - (2.0 * static_cast<double>(y) / (_height - 1));

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

        _completedLines++;
        if (_completedLines == 10) {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = now - _startTime;
            _pixelsPerSecond = (_completedLines * _width) / elapsed.count();
        }

        if (_showProgress && (_completedLines % 10 == 0 || _completedLines == _height)) {
            std::lock_guard<std::mutex> lock(_mutex);
            updateProgress();
        }
    }

    std::lock_guard<std::mutex> lock(_mutex);
    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < _width; x++) {
            _pixelBuffer[y][x] = localBuffer[y - startY][x];
        }
    }
}

void Renderer::renderPreview()
{
    int originalWidth = _width;
    int originalHeight = _height;
    _width = _previewWidth;
    _height = _previewHeight;
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
    for (int y = 0; y < _height; y++) {
        _pixelBuffer[y].resize(_width);
    }

    _completedLines = 0;
    _pixelsPerSecond = 0.0;
    _startTime = std::chrono::steady_clock::now();
    std::cout << "Starting preview render (" << _width << "x" << _height << ")..."
        << std::endl;

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

    std::cout << "\rPreview rendering: [";
    for (int i = 0; i < 50; ++i) {
        std::cout << "=";
    }
    std::cout << "] 100%                   " << std::endl;

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - _startTime;
    std::cout << "Preview render time: " << formatTime(elapsedTime.count()) << std::endl;

    savePreviewToFile();
    _width = originalWidth;
    _height = originalHeight;
}

void Renderer::savePreviewToFile()
{
    std::ofstream file(_previewOutputFile);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open preview file: " + _previewOutputFile);
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
}

void Renderer::render()
{
    _aspectRatio = static_cast<double>(_width) / _height;
    _pixelBuffer.resize(_height, std::vector<Graphic::color_t>(_width));
    for (int y = 0; y < _height; y++) {
        _pixelBuffer[y].resize(_width);
    }

    _completedLines = 0;
    _pixelsPerSecond = 0.0;
    _startTime = std::chrono::steady_clock::now();
    std::cout << "Starting full render of " << _width << "x" << _height
              << " image (" << _height * _width << " pixels)..." << std::endl;

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

    std::cout << "\rRendering: [";
    for (int i = 0; i < 50; ++i) {
        std::cout << "=";
    }
    std::cout << "] 100%" << std::endl;
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - _startTime;
    std::cout << "Total render time: " << formatTime(elapsedTime.count()) << std::endl;
    std::cout << "Average pixels per second: " << std::fixed << std::setprecision(0)
              << (_width * _height) / elapsedTime.count() << std::endl;

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
}
