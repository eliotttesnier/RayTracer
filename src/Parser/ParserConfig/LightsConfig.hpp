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
        const std::vector<std::tuple<double, double, double>> _directional;
        const std::tuple<double, double, double> _position;
        const double _ambient;
        const double _diffuse;
    public:

        double getAmbient() const;

        double getDiffuse() const;

        std::tuple<double, double, double> getPosition() const;

        std::vector<std::tuple<double, double, double>> getDirectional() const;

        LightsConfig() = delete;
        LightsConfig(const std::vector<std::tuple<double, double, double>> &directional,
                    const std::tuple<double, double, double> &position,
                    const double ambient,
                    const double diffuse);
        ~LightsConfig() = default;
    };

} // Parser
} // raytracer

#endif //LIGHTCONFIG_HPP
