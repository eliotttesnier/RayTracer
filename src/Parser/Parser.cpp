//
// Created by roussierenoa on 4/30/25.
//

#include "Parser.hpp"
#include <iostream>
#include <string>
#include <libconfig.h++>


void raytracer::Parser::Parser::_getCameraData(const libconfig::Setting &root) {
    const auto &camera = root["camera"];
    const auto &res = camera["resolution"];
    const auto &pos = camera["position"];
    const auto &rot = camera["rotation"];

    int width = res.lookup("width");
    int height = res.lookup("height");
    double x = pos.lookup("x");
    double y = pos.lookup("y");
    double z = pos.lookup("z");

    double rx = rot.lookup("x");
    double ry = rot.lookup("y");
    double rz = rot.lookup("z");
    double fov = camera["fieldOfView"];
#ifdef _DEBUG
    std::cout << "Camera: " << width << "x" << height << ", pos(" << x << ", " << y << ", " << z << "), rota(" << rx << ", " << ry << ", " << rz << "), fov(" << fov << ")" << std::endl;;
#endif
    this->_camConfig = std::make_unique<CameraConfig>(std::make_tuple(width, height), std::make_tuple(x, y, z), std::make_tuple(rx, ry, rz), fov);
}

void raytracer::Parser::Parser::_getPrimitivesData(const libconfig::Setting &root)
{
    std::vector<std::pair<std::tuple<double, double, double, double>, std::tuple<int, int, int>>> spheresVector;
    const auto &spheres = root["primitives"]["spheres"];
    for (int i = 0; i < spheres.getLength(); ++i) {
        const auto &s = spheres[i];
        double px = s["x"];
        double py = s["y"];
        double pz = s["z"];
        double radius = s["r"];
        const auto &color = s["color"];
        int cr = color["r"], cg = color["g"], cb = color["b"];
        spheresVector.emplace_back(std::make_tuple(px, py, pz, radius), std::make_tuple(cr, cg, cb));
#ifdef _DEBUG
        std::cout << "Sphere: pos(" << px << ", " << py << ", " << pz << "), r=" << radius
                  << ", color(" << cr << ", " << cg << ", " << cb << ")\n";
#endif
    }
    std::vector<std::tuple<char, double, std::tuple<int, int, int>>> planesVector;
    const auto &planes = root["primitives"]["planes"];
    for (int i = 0; i < planes.getLength(); ++i) {
        const auto &p = planes[i];
        std::string axis = p["axis"];
        double pos = p["position"];
        const auto &color = p["color"];
        int cr = color["r"];
        int cg = color["g"];
        int cb = color["b"];
        planesVector.emplace_back(axis[0], pos, std::make_tuple(cr, cg, cb));
#ifdef _DEBUG
        std::cout << "Plane: axis=" << axis << ", position=" << pos
                  << ", color(" << cr << ", " << cg << ", " << cb << ")\n";
#endif
    }

    std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> cylinderVector;
    const auto &cylinder = root["primitives"]["cylinders"];
    for (int i = 0; i < cylinder.getLength(); ++i) {
        const auto &s = cylinder[i];
        double px = s["x"];
        double py = s["y"];
        double pz = s["z"];
        double radius = s["r"];
        double height = s["h"];
        const auto &color = s["color"];
        int cr = color["r"], cg = color["g"], cb = color["b"];
        cylinderVector.emplace_back(std::make_tuple(px, py, pz, radius, height), std::make_tuple(cr, cg, cb));
#ifdef _DEBUG
        std::cout << "Cylinder: pos(" << px << ", " << py << ", " << pz << "), r=" << radius << ", h=" << height
                  << ", color(" << cr << ", " << cg << ", " << cb << ")\n";
#endif
    }

    std::vector<std::pair<std::tuple<double, double, double, double, double>, std::tuple<int, int, int>>> coneVector;
    const auto &cone = root["primitives"]["cones"];
    for (int i = 0; i < cone.getLength(); ++i) {
        const auto &s = cone[i];
        double px = s["x"];
        double py = s["y"];
        double pz = s["z"];
        double radius = s["r"];
        double height = s["h"];
        const auto &color = s["color"];
        int cr = color["r"], cg = color["g"], cb = color["b"];
        coneVector.emplace_back(std::make_tuple(px, py, pz, radius, height), std::make_tuple(cr, cg, cb));
#ifdef _DEBUG
        std::cout << "Cone: pos(" << px << ", " << py << ", " << pz << "), r=" << radius << ", h=" << height
                  << ", color(" << cr << ", " << cg << ", " << cb << ")\n";
#endif
    }

    this->_primitiveConfig = std::make_unique<PrimitivesConfig>(spheresVector, planesVector, cylinderVector, coneVector);
}

std::tuple<double, std::tuple<int, int, int>> raytracer::Parser::Parser::_getAmbientData(const libconfig::Setting &root)
{
    std::tuple<double, std::tuple<int, int, int>> ambientData;
    const auto &ambient = root["lights"]["ambient"];
    const auto &s = ambient[0];
    double intensity = s["intensity"];
    const auto &color = s["color"];
    int cr = color["r"];
    int cg = color["g"];
    int cb = color["b"];
    ambientData = std::make_tuple(intensity, std::make_tuple(cr, cg, cb));
#ifdef _DEBUG
    std::cout << "Ambient Light: intensity= "<< intensity
              << ", color(" << cr << ", " << cg << ", " << cb << ")" << std::endl;
#endif
    return ambientData;
}

std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> raytracer::Parser::Parser::_getDirectionalData(const libconfig::Setting &root)
{
    std::vector<std::tuple<double, std::tuple<double, double, double>, std::tuple<double, double, double>, std::tuple<int, int, int>>> directionalData;
    const auto &directional = root["lights"]["directional"];
    const auto &s = directional[0];
    double intensity = s["intensity"];
    const auto &direction = s["direction"];
    double dx = direction["x"];
    double dy = direction["y"];
    double dz = direction["z"];
    const auto &position = s["position"];
    double px = position["x"];
    double py = position["y"];
    double pz = position["z"];
    const auto &color = s["color"];
    int cr = color["r"];
    int cg = color["g"];
    int cb = color["b"];
    directionalData.emplace_back(intensity, std::make_tuple(px, py, pz), std::make_tuple(dx, dy, dz), std::make_tuple(cr, cg, cb));
#ifdef _DEBUG
    std::cout << "Directional Light: intensity= "<< intensity
              << ", direction(" << dx << ", " << dy << ", " << dz << ")"
              << ", position(" << px << ", " << py << ", " << pz << ")"
              << ", color(" << cr << ", " << cg << ", " << cb << ")" << std::endl;
#endif
    return directionalData;
}

void raytracer::Parser::Parser::_getLightsData(const libconfig::Setting &root)
{
    auto ambient = this->_getAmbientData(root);
    auto directional = this->_getDirectionalData(root);
    this->_lightConfig = std::make_unique<LightsConfig>(ambient, directional);
}

raytracer::Parser::CameraConfig raytracer::Parser::Parser::getCameraConfig() const {
    return *this->_camConfig;
}

raytracer::Parser::LightsConfig raytracer::Parser::Parser::getLightConfig() const {
    return *this->_lightConfig;
}

raytracer::Parser::PrimitivesConfig raytracer::Parser::Parser::getPrimitivesConfig() const {
    return *this->_primitiveConfig;
}

raytracer::Parser::Parser::Parser(char *path) {
    libconfig::Config cfg;

    try {
        cfg.readFile(path);
    } catch (const libconfig::FileIOException &e) {
        std::cerr << "[ERROR] I/O error while reading config file: " << path << "\n";
        throw;
    } catch (const libconfig::ParseException &e) {
        std::cerr << "[ERROR] Parse error at " << e.getFile() << ":" << e.getLine()
                  << " - " << e.getError() << "\n";
        throw;
    }

    try {
        const libconfig::Setting &root = cfg.getRoot();
        this->_getCameraData(root);
        this->_getLightsData(root);
        this->_getPrimitivesData(root);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[ERROR] Missing setting: " << e.getPath() << "\n";
        throw;
    }
}
