//
// Created by roussierenoa on 4/30/25.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <libconfig.h++>
#include <memory>
#include <vector>

namespace raytracer::Parser {
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

    class LightConfig {
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

        LightConfig() = delete;
        LightConfig(const std::vector<std::tuple<double, double, double>> &directional,
                    const std::tuple<double, double, double> &position,
                    const double ambient,
                    const double diffuse);
        ~LightConfig() = default;
    };


    class PrimitiveConfig {
        std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> _sphere; // Position + raduis, Color
        std::vector<std::tuple<char, double, std::tuple<int, int, int>>> _plane; // axis, position, Color
    public:
        std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> getSpheres() const;

        std::vector<std::tuple<char, double, std::tuple<int, int, int>>> getPlanes() const;

        PrimitiveConfig() = delete;
        PrimitiveConfig(const std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> &sphere,
                        const std::vector<std::tuple<char, double, std::tuple<int, int, int>>> &plane);
        ~PrimitiveConfig() = default;
    };

    class Parser {
    private:
        std::unique_ptr<CameraConfig> _camConfig;
        std::unique_ptr<LightConfig> _lightConfig;
        std::unique_ptr<PrimitiveConfig> _primitiveConfig;

        void _getCameraData(const libconfig::Setting &root);
        void _getPrimitivesData(const libconfig::Setting &root);
        void _getLightsData(const libconfig::Setting &root);
    public:

        CameraConfig getCameraConfig() const;
        LightConfig getLightConfig() const;
        PrimitiveConfig getPrimitivesConfig() const;

        Parser() = delete;
        Parser(char *path);
        ~Parser() = default;
    };
}



#endif //PARSER_HPP
