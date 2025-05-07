//
// Created by roussierenoa on 4/30/25.
//

#ifndef CAMERACONFIG_HPP
#define CAMERACONFIG_HPP
#include <vector>
#include <memory>

namespace RayTracer {
namespace Parser {

typedef std::tuple<int, int> resolution_t; // Resolution
typedef std::tuple<double, double, double> truple_t; // Position || Rotation

class CameraConfig {
    private:
        const resolution_t _resolution;
        const truple_t _position;
        const truple_t _rotation;
        const double _fov;
    public:
        double getFov() const;

        resolution_t getResolution() const;

        truple_t getPosition() const;

        truple_t getRotation() const;

        CameraConfig() = delete;
        CameraConfig(
            const resolution_t &resolution,
            const truple_t &position,
            const truple_t &rotation,
            const double fov
        );
        ~CameraConfig() = default;
};

} // Parser
} // raytracer

#endif //CAMERACONFIG_HPP
