//
// Created by roussierenoa on 5/1/25.
//

#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <vector>
#include <map>

#include "../Parser/ParserConfig/CameraConfig.hpp"
#include "../Parser/ParserConfig/PrimitivesConfig.hpp"
#include "../Parser/ParserConfig/LightsConfig.hpp"
#include "../Primitives/IPrimitive.hpp"
#include "../Lights/ILight.hpp"
#include "CameraFactory/CameraFactory.hpp"
#include "LibLoader/LibLoader.hpp"


namespace RayTracer::Factory {

typedef std::tuple<std::vector<std::shared_ptr<IPrimitive>>, std::vector<std::shared_ptr<ILight>>, std::shared_ptr<RayTracer::Camera>> scene_t;
class Factory {
    public:
        static scene_t createElement(
            const Parser::CameraConfig &camera,
            const Parser::PrimitivesConfig &scene,
            const Parser::LightsConfig &light,
            const std::map<std::string, std::shared_ptr<Loader::LibLoader>> &plugins
        );
        Factory() = default;
        ~Factory() = default;
};

} // Raytracer::Factory

#endif //FACTORY_HPP
