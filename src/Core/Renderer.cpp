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

namespace AnsiColor {
const std::string RESET      = "\033[0m";
const std::string BOLD       = "\033[1m";
const std::string UNDERLINE  = "\033[4m";
const std::string BLACK      = "\033[30m";
const std::string RED        = "\033[31m";
const std::string GREEN      = "\033[32m";
const std::string YELLOW     = "\033[33m";
const std::string BLUE       = "\033[34m";
const std::string MAGENTA    = "\033[35m";
const std::string CYAN       = "\033[36m";
const std::string WHITE      = "\033[37m";
const std::string BG_BLACK   = "\033[40m";
const std::string BG_RED     = "\033[41m";
const std::string BG_GREEN   = "\033[42m";
const std::string BG_YELLOW  = "\033[43m";
const std::string BG_BLUE    = "\033[44m";
const std::string BG_MAGENTA = "\033[45m";
const std::string BG_CYAN    = "\033[46m";
const std::string BG_WHITE   = "\033[47m";
}

Renderer::Renderer(const std::shared_ptr<RayTracer::Camera> camera,
    const std::vector<std::shared_ptr<IPrimitive>> primitives,
    const std::vector<std::shared_ptr<ILight>> lights)
    : _camera(camera), _primitives(primitives), _lights(lights),
    _outputFile("output.ppm"), _previewOutputFile("preview.ppm"), _stopThreads(false)
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

void Renderer::setLight(const std::vector<std::shared_ptr<ILight>> &lights) {
    _lights = lights;
}

void Renderer::setPrimitives(const std::vector<std::shared_ptr<IPrimitive>> &primitives)
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

void Renderer::stopThreads()
{
    _stopThreads = true;
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
    int completedPixels = _completedPixels.load();
    int totalPixels = _width * _height;
    int percentage = (completedPixels * 100) / totalPixels;

    std::cout << "\r" << AnsiColor::BOLD << "Rendering:"
        << AnsiColor::RESET << " [" << AnsiColor::CYAN;
    int barWidth = 50;
    int pos = barWidth * percentage / 100;

    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << AnsiColor::GREEN << ">" << AnsiColor::CYAN;
        else std::cout << " ";
    }

    std::cout << AnsiColor::RESET << "] " << AnsiColor::BOLD << AnsiColor::YELLOW
              << std::setw(3) << percentage << "%" << AnsiColor::RESET;

    if (completedPixels > 0) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - _startTime;
        double pixelsPerSec = completedPixels / elapsed.count();
        _pixelsPerSecond = pixelsPerSec;

        double remainingPixels = totalPixels - completedPixels;
        double estimatedRemainingSeconds = remainingPixels / _pixelsPerSecond;

        std::cout << " | " << AnsiColor::CYAN << completedPixels << "/" << totalPixels
                  << " pixels" << AnsiColor::RESET
                  << " | " << AnsiColor::GREEN << std::fixed << std::setprecision(1)
                  << pixelsPerSec / 1000 << "k px/s" << AnsiColor::RESET
                  << " | " << AnsiColor::MAGENTA << "Remaining: "
                  << AnsiColor::BOLD << formatTime(estimatedRemainingSeconds)
                  << AnsiColor::RESET << "                                 ";
    }

    std::cout << std::flush;
}

void Renderer::renderSegment(int startY, int endY)
{
    std::vector<std::vector<Graphic::color_t>> localBuffer(endY - startY,
        std::vector<Graphic::color_t>(_width));

    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < _width; x++) {
            if (_stopThreads.load()) {
                return;
            }

            double u = (2.0 * static_cast<double>(x) / (_width - 1)) - 1.0;
            double v = 1.0 - (2.0 * static_cast<double>(y) / (_height - 1));

            Graphic::color_t pixelColor;

            switch (_antialiasingMode) {
                case SUPERSAMPLING:
                    pixelColor = supersample(u, v, _supersamplingLevel);
                    break;
                case ADAPTIVE_SUPERSAMPLING:
                    pixelColor = adaptiveSupersample(u, v, _adaptiveThreshold);
                    break;
                case NONE:
                default:
                    Math::Ray ray = _camera->ray(u, v);
                    pixelColor = traceRay(ray);
                    break;
            }

            localBuffer[y - startY][x] = pixelColor;
            _completedPixels++;

            if (_showProgress && (_completedPixels % 500 == 0)) {
                std::lock_guard<std::mutex> lock(_mutex);
                updateProgress();
            }
        }

        if (_renderingMode == PROGRESSIVE) {
            std::lock_guard<std::mutex> lock(_mutex);
            for (int x = 0; x < _width; x++) {
                _pixelBuffer[y][x] = localBuffer[y - startY][x];
            }
            notifyPixelUpdate();
        }

        if (_completedPixels == _width * 10) {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = now - _startTime;
            _pixelsPerSecond = _completedPixels / elapsed.count();
        }
    }

    if (_renderingMode != PROGRESSIVE) {
        std::lock_guard<std::mutex> lock(_mutex);
        for (int y = startY; y < endY; y++) {
            for (int x = 0; x < _width; x++) {
                _pixelBuffer[y][x] = localBuffer[y - startY][x];
            }
        }
    }
    notifyPixelUpdate();
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

    _completedPixels = 0;
    _pixelsPerSecond = 0.0;
    _startTime = std::chrono::steady_clock::now();
    std::cout << AnsiColor::CYAN << AnsiColor::BOLD << "⚡ Starting preview render "
              << AnsiColor::RESET << "(" << AnsiColor::YELLOW << _width << "x" << _height
              << AnsiColor::RESET << ")..." << std::endl;

    if (_useMultithreading) {
        unsigned int numThreads = std::min(std::thread::hardware_concurrency(), _maxThreads);
        std::vector<std::thread> threads;
        const int linesPerThread = _height / numThreads;

        try {
            for (unsigned int i = 0; i < numThreads; i++) {
                int startY = i * linesPerThread;
                int endY = (i == numThreads - 1) ? _height : (i + 1) * linesPerThread;
                threads.emplace_back(&Renderer::renderSegment, this, startY, endY);
            }

            for (auto &thread : threads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
        } catch (const std::exception &e) {
            for (auto &thread : threads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
            throw;
        }
    } else {
        renderSegment(0, _height);
    }

    std::cout << "\r" << AnsiColor::BOLD << "Preview rendering:"
        << AnsiColor::RESET << " [" << AnsiColor::GREEN;
    for (int i = 0; i < 50; ++i) {
        std::cout << "=";
    }
    std::cout << AnsiColor::RESET << "] " << AnsiColor::BOLD << AnsiColor::YELLOW
              << "100%" << AnsiColor::RESET
              << "                                                 " << std::endl;

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - _startTime;
    std::cout << AnsiColor::MAGENTA << "Preview render time: " << AnsiColor::BOLD
              << formatTime(elapsedTime.count()) << AnsiColor::RESET << std::endl;

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

    _completedPixels = 0;
    _pixelsPerSecond = 0.0;
    _startTime = std::chrono::steady_clock::now();
    std::cout << AnsiColor::CYAN << AnsiColor::BOLD << "🚀 Starting full render "
              << AnsiColor::RESET << "(" << AnsiColor::YELLOW << _width << "x" << _height
              << AnsiColor::RESET << " = " << AnsiColor::YELLOW << _height * _width
              << AnsiColor::RESET << " pixels)";

    if (_useMultithreading) {
        unsigned int numThreads = std::min(std::thread::hardware_concurrency(), _maxThreads);
        std::cout << AnsiColor::CYAN << " (Using " << AnsiColor::BOLD << numThreads
                  << AnsiColor::RESET << AnsiColor::CYAN << " threads for rendering)"
                  << AnsiColor::RESET << std::endl;

        std::vector<std::thread> threads;
        const int linesPerThread = _height / numThreads;

        try {
            for (unsigned int i = 0; i < numThreads; i++) {
                int startY = i * linesPerThread;
                int endY = (i == numThreads - 1) ? _height : (i + 1) * linesPerThread;
                threads.emplace_back(&Renderer::renderSegment, this, startY, endY);
            }

            for (auto &thread : threads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
        } catch (const std::exception &e) {
            for (auto &thread : threads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
            throw;
        }
    } else {
        std::cout << AnsiColor::CYAN << " (Single-threaded rendering)"
                  << AnsiColor::RESET << std::endl;
        renderSegment(0, _height);
    }

    if (_stopThreads.load()) {
        std::cout << std::endl << std::endl;
        return;
    }
    std::cout << "\r" << AnsiColor::BOLD << "Rendering:"
        << AnsiColor::RESET << " [" << AnsiColor::GREEN;
    for (int i = 0; i < 50; ++i) {
        std::cout << "=";
    }
    std::cout << AnsiColor::RESET << "] " << AnsiColor::BOLD << AnsiColor::YELLOW
              << "100%" << AnsiColor::RESET <<
              "                                                     " << std::endl;

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - _startTime;

    std::cout << AnsiColor::MAGENTA << "Total render time: " << AnsiColor::BOLD
              << formatTime(elapsedTime.count()) << AnsiColor::RESET << std::endl;

    double pixelsPerSec = (_width * _height) / elapsedTime.count();
    std::cout << AnsiColor::CYAN << "Average pixels per second: " << AnsiColor::BOLD
              << std::fixed << std::setprecision(0) << pixelsPerSec
              << AnsiColor::RESET << std::endl;

    std::cout << AnsiColor::GREEN << "✅ Rendering complete! Saving to "
              << AnsiColor::UNDERLINE << _outputFile << AnsiColor::RESET << std::endl;

    if (_renderingMode == PROGRESSIVE)
        notifyPixelUpdate(true);
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

void Renderer::setAntialiasingMode(AntialiasingMode mode)
{
    _antialiasingMode = mode;
}

void Renderer::setSupersamplingLevel(int level)
{
    if (level >= 1) {
        _supersamplingLevel = level;
    }
}

void Renderer::setAdaptiveThreshold(double threshold)
{
    if (threshold > 0.0 && threshold <= 1.0) {
        _adaptiveThreshold = threshold;
    }
}

void Renderer::setMultithreading(bool useMultithreading)
{
    _useMultithreading = useMultithreading;
}

Graphic::color_t Renderer::traceRay(const Math::Ray& ray) const
{
    double closestDist = std::numeric_limits<double>::max();
    bool hit = false;
    Graphic::color_t pixelColor = {0.0, 0.0, 0.0, 1.0};
    Math::hitdata_t closestHitData;
    std::shared_ptr<IPrimitive> closestPrimitive;

    for (const auto &primitive : _primitives) {
        Math::hitdata_t hitData = primitive->intersect(ray);

        if (hitData.hit && hitData.distance < closestDist) {
            closestDist = hitData.distance;
            closestHitData = hitData;
            closestPrimitive = primitive;
            hit = true;
        }
    }

    if (hit) {
        return closestPrimitive->getColor(
            closestHitData,
            ray,
            _lights,
            _primitives
        );
    }

    return pixelColor;
}

double Renderer::colorDifference(const Graphic::color_t& c1, const Graphic::color_t& c2) const
{
    double dr = c1.r - c2.r;
    double dg = c1.g - c2.g;
    double db = c1.b - c2.b;

    return std::sqrt(dr*dr + dg*dg + db*db) / (std::sqrt(3.0) * 255.0);
}

Graphic::color_t Renderer::averageColors(const std::vector<Graphic::color_t> &colors) const
{
    if (colors.empty())
        return {0.0, 0.0, 0.0, 1.0};

    double r = 0.0, g = 0.0, b = 0.0, a = 0.0;

    for (const auto &color : colors) {
        r += color.r;
        g += color.g;
        b += color.b;
        a += color.a;
    }

    int size = colors.size();
    return {
        r / size,
        g / size,
        b / size,
        a / size
    };
}

Graphic::color_t Renderer::supersample(double u, double v, int samples) const
{
    std::vector<Graphic::color_t> colors;
    colors.reserve(samples * samples);

    const double step = 1.0 / (_width * samples);
    const double startU = u - step * (samples - 1) / 2.0;
    const double startV = v - step * (samples - 1) / 2.0;

    for (int sy = 0; sy < samples; sy++) {
        for (int sx = 0; sx < samples; sx++) {
            double sampleU = startU + sx * step;
            double sampleV = startV + sy * step;

            Math::Ray ray = _camera->ray(sampleU, sampleV);
            colors.push_back(traceRay(ray));
        }
    }

    return averageColors(colors);
}

bool Renderer::needsFurtherSampling(const Graphic::color_t& tl, const Graphic::color_t& tr,
                               const Graphic::color_t& bl, const Graphic::color_t& br,
                               double threshold) const
{
    double diff1 = colorDifference(tl, tr);
    double diff2 = colorDifference(tl, bl);
    double diff3 = colorDifference(tr, br);
    double diff4 = colorDifference(bl, br);
    double diff5 = colorDifference(tl, br);
    double diff6 = colorDifference(tr, bl);

    return (diff1 > threshold || diff2 > threshold || diff3 > threshold ||
            diff4 > threshold || diff5 > threshold || diff6 > threshold);
}

Graphic::color_t Renderer::adaptiveSupersample(double u, double v, double threshold) const
{
    const double pixelWidth = 2.0 / _width;
    const double pixelHeight = 2.0 / _height;
    const double halfPixelW = pixelWidth * 0.5;
    const double halfPixelH = pixelHeight * 0.5;

    Math::Ray rayTL = _camera->ray(u - halfPixelW, v + halfPixelH);
    Math::Ray rayTR = _camera->ray(u + halfPixelW, v + halfPixelH);
    Math::Ray rayBL = _camera->ray(u - halfPixelW, v - halfPixelH);
    Math::Ray rayBR = _camera->ray(u + halfPixelW, v - halfPixelH);

    Graphic::color_t colorTL = traceRay(rayTL);
    Graphic::color_t colorTR = traceRay(rayTR);
    Graphic::color_t colorBL = traceRay(rayBL);
    Graphic::color_t colorBR = traceRay(rayBR);

    std::vector<Graphic::color_t> colors = {colorTL, colorTR, colorBL, colorBR};

    if (needsFurtherSampling(colorTL, colorTR, colorBL, colorBR, threshold)) {
        Math::Ray rayCenter = _camera->ray(u, v);
        Math::Ray rayTop = _camera->ray(u, v + halfPixelH);
        Math::Ray rayRight = _camera->ray(u + halfPixelW, v);
        Math::Ray rayBottom = _camera->ray(u, v - halfPixelH);
        Math::Ray rayLeft = _camera->ray(u - halfPixelW, v);

        colors.push_back(traceRay(rayCenter));
        colors.push_back(traceRay(rayTop));
        colors.push_back(traceRay(rayRight));
        colors.push_back(traceRay(rayBottom));
        colors.push_back(traceRay(rayLeft));
    }

    return averageColors(colors);
}

void Renderer::setRenderingMode(RenderingMode mode)
{
    _renderingMode = mode;
    _lastUpdateTime = std::chrono::steady_clock::now();
}

void Renderer::setMaxThreads(unsigned int maxThreads)
{
    _maxThreads = maxThreads;
}

void Renderer::registerUpdateCallback(std::function<void(
    const std::vector<std::vector<Graphic::color_t>>&)> callback)
{
    _updateCallback = callback;
}

const std::vector<std::vector<Graphic::color_t>> &Renderer::getPixelBuffer() const
{
    return _pixelBuffer;
}

void Renderer::notifyPixelUpdate(bool force)
{
    if (_renderingMode != PROGRESSIVE || !_updateCallback) {
        return;
    }

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                now - _lastUpdateTime).count();

    if (elapsed >= 100 || force) {
        _updateCallback(_pixelBuffer);
        _lastUpdateTime = now;
    }
}
