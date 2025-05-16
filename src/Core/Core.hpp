//
// Created by roussierenoa on 5/2/25.
//

#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include <map>
#include <string>

#include "Factory/Factory.hpp"
#include "LibLoader/LibLoader.hpp"
#include "Parser/Parser.hpp"
#include "Renderer.hpp"
#include "../GraphicRenderer/GraphicRenderer.hpp"

namespace RayTracer {

class Core {
    private:
        std::unique_ptr<RayTracer::Parser::Parser> _parser;
        std::map<std::string, std::shared_ptr<Loader::LibLoader>> _plugins;
        std::tuple<
            std::vector<std::shared_ptr<IPrimitive>>,
            std::vector<std::shared_ptr<ILight>>,
            std::shared_ptr<RayTracer::Camera>
        > _sceneElements;
        std::unique_ptr<GraphicRenderer> _graphicRenderer;
        bool _graphicRendererInitialized = false;

        Math::Point3D _cameraOffset;
        void _loadPlugins();
        void _handleCameraMovement(const std::string &configFileName, runResult_e result);
        void _runProg(const std::string &configFileName, const Math::Point3D &additionalOffset);

    public:
        explicit Core(char **av);
        ~Core() = default;

        std::vector<std::shared_ptr<IPrimitive>> getPrimitives() const;
        std::vector<std::shared_ptr<ILight>> getLights() const;
        std::shared_ptr<RayTracer::Camera> getCamera() const;
        void applyAntialiasing(const std::unique_ptr<Renderer> &renderer) const;
        void applyRenderingConfig(const std::unique_ptr<Renderer> &renderer) const;

}; // Core

} // RayTracer

#endif //CORE_HPP
