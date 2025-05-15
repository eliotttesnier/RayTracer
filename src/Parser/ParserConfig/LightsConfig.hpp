//
// Created by roussierenoa on 4/30/25.
//

#ifndef LIGHTCONFIG_HPP
#define LIGHTCONFIG_HPP
#include <memory>
#include <vector>

namespace RayTracer {
namespace Parser {

typedef std::tuple<double, double, double> truple_t;
typedef std::tuple<int, int, int> color_t;

typedef std::tuple<double, truple_t, truple_t, color_t> directional_t; // Intensity, position, direction, color
typedef std::tuple<double, truple_t, color_t> point_t; // Intensity, position, color
typedef std::tuple<double, color_t> ambient_t; // Intensity, color

class LightsConfig {
    private:
        const std::vector<directional_t>  _directional;
        const std::vector<point_t>  _point;
        const ambient_t _ambient;

    public:
        ambient_t getAmbient() const;
        std::vector<directional_t> getDirectional() const;
        std::vector<point_t> getPoint() const;

        LightsConfig() = delete;
        LightsConfig(
            const ambient_t &ambient, // Intensity, color
            const std::vector<directional_t> &directional, // Intensity, position, direction, color
            const std::vector<point_t> &point // Intensity, position, color
        );
        ~LightsConfig() = default;
};

} // Parser
} // raytracer

#endif //LIGHTCONFIG_HPP
