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

class Factory {
private:
public:
    static std::tuple<std::vector<std::unique_ptr<IPrimitive>>, std::vector<std::unique_ptr<ILight>>, std::unique_ptr<RayTracer::Camera>> createElement(const Parser::CameraConfig &camera,
                                                      const Parser::PrimitivesConfig &scene,
                                                      const Parser::LightsConfig &light,
                                                      std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins);
    Factory() = default;
    ~Factory() = default;
};

} // Raytracer::Factory

#endif //FACTORY_HPP
