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
#include "../Primitives/IPrimitive.hpp"
#include "../Graphic/Camera.hpp"
#include "../Graphic/Color.hpp"

class Renderer {
    public:
        Renderer(const RayTracer::Camera& camera, const std::vector<std::shared_ptr<IPrimitive>>& primitives);
        ~Renderer();

        void setCamera(const RayTracer::Camera& camera);
        void setPrimitives(const std::vector<std::shared_ptr<IPrimitive>>& primitives);
        void setResolution(int width, int height);
        void setOutputFile(const std::string& outputFile);
        void render();

    protected:
    private:
        void renderSegment(int startY, int endY);
        void saveToFile();

        RayTracer::Camera _camera;
        std::vector<std::shared_ptr<IPrimitive>> _primitives;
        std::vector<std::vector<Graphic::color_t>> _pixelBuffer;
        std::string _outputFile;
        int _width;
        int _height;
        double _aspectRatio;
        std::mutex _mutex;
};

#endif /* !RENDERER_HPP_ */
