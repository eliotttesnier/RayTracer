//
// Created by roussierenoa on 5/1/25.
//

#ifndef CAMERAFACTORY_HPP
#define CAMERAFACTORY_HPP
#include "../../Graphic/Camera.hpp"
#include "../../Parser/ParserConfig/CameraConfig.hpp"
#include <vector>
#include <memory>

namespace raytracer {
namespace Factory {

class CameraFactory {
    static std::vector<std::unique_ptr<RayTracer::Camera>> createCamera(const raytracer::Parser::CameraConfig &config);
    CameraFactory() = default;
    ~CameraFactory() = delete;
};

} // Factory
} // raytracer

#endif //CAMERAFACTORY_HPP
