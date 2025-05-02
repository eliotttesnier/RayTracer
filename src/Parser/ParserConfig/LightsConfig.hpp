//
// Created by roussierenoa on 4/30/25.
//

#ifndef LIGHTCONFIG_HPP
#define LIGHTCONFIG_HPP
#include <memory>
#include <vector>

namespace raytracer {
namespace Parser {
    class LightsConfig {
    private:
        const std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>>  _directional;
        const std::tuple<double, std::tuple<int, int, int>> _ambient;
    public:

        std::tuple<double, std::tuple<int, int, int>> getAmbient() const;

        std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> getDirectional() const;

        LightsConfig() = delete;
        LightsConfig(const std::tuple<double, std::tuple<int, int, int>> &ambiant, /* Intensité couleur */
                     const std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> &diffuse /* Intenstié, position, direction, couleur */);
        ~LightsConfig() = default;
    };

} // Parser
} // raytracer

#endif //LIGHTCONFIG_HPP
