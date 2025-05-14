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
        const ambient_t _ambient;

    public:
        ambient_t getAmbient() const;
        std::vector<directional_t> getDirectional() const;

        LightsConfig() = delete;
        LightsConfig(
            const ambient_t &ambiant, /* Intensité couleur */
            const std::vector<directional_t> &directional /* Intenstié, position, direction, couleur */
        );
        ~LightsConfig() = default;
};

} // Parser
} // raytracer

#endif //LIGHTCONFIG_HPP
