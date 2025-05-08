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
#include "../Primitives/IPrimitive.hpp"
#include "../Lights/ILight.hpp"
#include "../Graphic/Camera.hpp"
#include "../Graphic/Color.hpp"

class Renderer {
    public:
        Renderer(const std::shared_ptr<RayTracer::Camera> camera, const std::vector<std::shared_ptr<IPrimitive>> primitives,
                const std::vector<std::shared_ptr<ILight>> lights);
        ~Renderer();

        void setCamera(const std::shared_ptr<RayTracer::Camera> camera);
        void setLight(const std::vector<std::shared_ptr<ILight>> &lights);
        void setPrimitives(const std::vector<std::shared_ptr<IPrimitive>>& primitives);
        void setResolution(int width, int height);
        void setOutputFile(const std::string& outputFile);
        void render();

    protected:
    private:
        void renderSegment(int startY, int endY);
        void saveToFile();
        void updateProgress();
        std::string formatTime(double seconds);

        std::shared_ptr<RayTracer::Camera> _camera;
        std::vector<std::shared_ptr<IPrimitive>> _primitives;
        std::vector<std::shared_ptr<ILight>> _lights;
        std::vector<std::vector<Graphic::color_t>> _pixelBuffer;
        std::string _outputFile;
        int _width;
        int _height;
        double _aspectRatio;
        double _fov;
        std::mutex _mutex;
        std::atomic<int> _completedLines{0};
        bool _showProgress{true};
        std::chrono::time_point<std::chrono::steady_clock> _startTime;
        double _pixelsPerSecond{0.0};
};

#endif /* !RENDERER_HPP_ */
