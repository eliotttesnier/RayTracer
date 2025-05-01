//
// Created by roussierenoa on 4/30/25.
//

#ifndef CAMERACONFIG_HPP
#define CAMERACONFIG_HPP
#include <vector>
#include <memory>

namespace raytracer {
namespace Parser {

    class CameraConfig {
    private:
        const std::tuple<int, int> _resolution;
        const std::tuple<double, double, double> _position;
        const std::tuple<double, double, double> _rotation;
        const double _fov;
    public:
        std::tuple<int, int> getResolution() const;

        std::tuple<double, double, double> getPosition() const;

        std::tuple<double, double, double> getRotation() const;

        CameraConfig() = delete;
        CameraConfig(const std::tuple<int, int> &resolution,
                     const std::tuple<double, double, double> &position,
                     const std::tuple<double, double, double> &rotation,
                     const double fov);
        ~CameraConfig() = default;
    };

} // Parser
} // raytracer

#endif //CAMERACONFIG_HPP
