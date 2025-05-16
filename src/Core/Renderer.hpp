/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <functional>
#include "../Primitives/IPrimitive.hpp"
#include "../Lights/ILight.hpp"
#include "../Graphic/Camera.hpp"
#include "../Graphic/Color.hpp"

class Renderer {
    public:
        enum AntialiasingMode {
            NONE,
            SUPERSAMPLING,
            ADAPTIVE_SUPERSAMPLING
        };

        enum RenderingMode {
            PREVIEW,
            PROGRESSIVE
        };

        Renderer(const std::shared_ptr<RayTracer::Camera> camera, const std::vector<std::shared_ptr<IPrimitive>> primitives,
                const std::vector<std::shared_ptr<ILight>> lights);
        ~Renderer();

        void setCamera(const std::shared_ptr<RayTracer::Camera> camera);
        void setLight(const std::vector<std::shared_ptr<ILight>> &lights);
        void setPrimitives(const std::vector<std::shared_ptr<IPrimitive>> &primitives);
        void setResolution(int width, int height);
        void setOutputFile(const std::string& outputFile);
        void setAntialiasingMode(AntialiasingMode mode);
        void setSupersamplingLevel(int level);
        void setAdaptiveThreshold(double threshold);
        void setMultithreading(bool useMultithreading);
        void setMaxThreads(unsigned int maxThreads);
        void setRenderingMode(RenderingMode mode);
        void stopThreads();

        const std::vector<std::vector<Graphic::color_t>> &getPixelBuffer() const;
        
        void registerUpdateCallback(std::function<void(const std::vector<std::vector<Graphic::color_t>> &)> callback);
        void render();
        void renderPreview();

    protected:
    private:
        void renderSegment(int startY, int endY);
        void saveToFile();
        void savePreviewToFile();
        void updateProgress();
        void notifyPixelUpdate(bool force = false);
        std::string formatTime(double seconds);

        Graphic::color_t traceRay(const Math::Ray &ray) const;
        Graphic::color_t supersample(double u, double v, int samples) const;
        Graphic::color_t adaptiveSupersample(double u, double v, double threshold) const;
        bool needsFurtherSampling(
            const Graphic::color_t &tl,
            const Graphic::color_t &tr,
            const Graphic::color_t &bl,
            const Graphic::color_t &br,
            double threshold
        ) const;
        double colorDifference(const Graphic::color_t& c1, const Graphic::color_t &c2) const;
        Graphic::color_t averageColors(const std::vector<Graphic::color_t> &colors) const;

        std::shared_ptr<RayTracer::Camera> _camera;
        std::vector<std::shared_ptr<IPrimitive>> _primitives;
        std::vector<std::shared_ptr<ILight>> _lights;
        std::vector<std::vector<Graphic::color_t>> _pixelBuffer;
        std::string _outputFile;
        std::string _previewOutputFile;
        int _width;
        int _height;
        int _previewWidth;
        int _previewHeight;
        double _aspectRatio;
        double _fov;
        std::mutex _mutex;
        std::atomic<int> _completedPixels{0};
        bool _showProgress{true};
        std::chrono::time_point<std::chrono::steady_clock> _startTime;
        double _pixelsPerSecond{0.0};
        std::chrono::steady_clock::time_point _lastUpdateTime;
        std::function<void(const std::vector<std::vector<Graphic::color_t>> &)> _updateCallback;
        RenderingMode _renderingMode = PREVIEW;
        int _updateFrequency = 100;

        AntialiasingMode _antialiasingMode = NONE;
        int _supersamplingLevel = 4;
        double _adaptiveThreshold = 0.1;
        bool _useMultithreading{true};
        unsigned int _maxThreads = 8;

        std::atomic<bool> _stopThreads;
};

#endif /* !RENDERER_HPP_ */
