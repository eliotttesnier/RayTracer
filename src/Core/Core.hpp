//
// Created by roussierenoa on 5/2/25.
//

#ifndef CORE_HPP
#define CORE_HPP
#include <map>
#include <string>

#include "Factory/Factory.hpp"
#include "LibLoader/LibLoader.hpp"
#include "Parser/Parser.hpp"
#include "Renderer.hpp"

namespace RayTracer {

class Core {
private:
    RayTracer::Parser::Parser _parser;
    std::map<std::string, std::unique_ptr<Loader::LibLoader>> _plugins;
    std::tuple<
        std::vector<std::shared_ptr<IPrimitive>>,
        std::vector<std::shared_ptr<ILight>>,
        std::shared_ptr<RayTracer::Camera>
    > _sceneElements;

    void _loadPlugins();
public:

    explicit Core(char **av);
    ~Core() = default;

    std::vector<std::shared_ptr<IPrimitive>> getPrimitives() const;
    std::vector<std::shared_ptr<ILight>> getLights() const;
    std::shared_ptr<RayTracer::Camera> getCamera() const;
    void applyAntialiasing(Renderer& renderer) const;

}; // Core
} // RayTracer

#endif //CORE_HPP
