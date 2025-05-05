//
// Created by roussierenoa on 5/1/25.
//

#ifndef CAMERAFACTORY_HPP
#define CAMERAFACTORY_HPP
#include "../../Graphic/Camera.hpp"
#include "../../Parser/ParserConfig/CameraConfig.hpp"
#include <vector>
#include <memory>

namespace RayTracer {
namespace Factory {

class CameraFactory {
public:
    static std::shared_ptr<RayTracer::Camera> createCamera(const RayTracer::Parser::CameraConfig &config);
    CameraFactory() = default;
    ~CameraFactory() = delete;
};

} // Factory
} // raytracer

#endif //CAMERAFACTORY_HPP
