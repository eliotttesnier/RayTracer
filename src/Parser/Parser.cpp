//
// Created by roussierenoa on 4/30/25.
//

#include "Parser.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <libconfig.h++>

namespace RayTracer::Parser {

void Parser::_getCameraData(const libconfig::Setting &root)
{
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
        std::cout << "Camera: " << width << "x" << height << ", "
            << "pos(" << x << ", " << y << ", " << z << "), "
            << "rota(" << rx << ", " << ry << ", " << rz << "), "
            << "fov(" << fov << ")" << std::endl;
    #endif
    this->_camConfig = std::make_unique<CameraConfig>(
        std::make_tuple(width, height),
        std::make_tuple(x, y, z),
        std::make_tuple(rx, ry, rz),
        fov
    );
}

std::vector<sphere_t> Parser::_getSpheresData(const libconfig::Setting &root)
{
    std::vector<sphere_t> spheresVector;

    const auto &spheres = root["primitives"]["spheres"];

    for (int i = 0; i < spheres.getLength(); ++i) {
        const auto &s = spheres[i];
        const auto &position = s["position"];
        const auto &rotation = s["rotation"];
        const auto &scale = s["scale"];
        const auto &color = s["color"];
        double px = position["x"];
        double py = position["y"];
        double pz = position["z"];
        double rx = rotation["x"];
        double ry = rotation["y"];
        double rz = rotation["z"];
        double sx = scale["x"];
        double sy = scale["y"];
        double sz = scale["z"];
        double radius = s["r"];
        int cr = color["r"];
        int cg = color["g"];
        int cb = color["b"];
        spheresVector.emplace_back(
            std::make_tuple(px, py, pz, radius),
            std::make_tuple(rx, ry, rz),
            std::make_tuple(sx, sy, sz),
            std::make_tuple(cr, cg, cb)
        );
        #ifdef _DEBUG
            std::cout << "Sphere: pos(" << px << ", " << py << ", " << pz << "), "
                << "r=" << radius << ", "
                << "rota(" << rx << ", " << ry << ", " << rz << "), "
                << "color(" << cr << ", " << cg << ", " << cb << ")\n";
        #endif
    }

    return spheresVector;
}

std::vector<plane_t> Parser::_getPlanesData(const libconfig::Setting &root)
{
    std::vector<plane_t> planesVector;

    const auto &planes = root["primitives"]["planes"];

    for (int i = 0; i < planes.getLength(); ++i) {
        const auto &p = planes[i];
        std::string axis = p["axis"];
        const auto &position = p["position"];
        const auto &rotation = p["rotation"];
        const auto &scale = p["scale"];
        const auto &color = p["color"];
        double x = position["x"];
        double y = position["y"];
        double z = position["z"];
        double rx = rotation["x"];
        double ry = rotation["y"];
        double rz = rotation["z"];
        double sx = scale["x"];
        double sy = scale["y"];
        double sz = scale["z"];
        int cr = color["r"];
        int cg = color["g"];
        int cb = color["b"];
        double width = p["width"];
        double height = p["height"];
        planesVector.emplace_back(
            axis[0],
            std::make_tuple(x, y, z),
            std::make_tuple(rx, ry, rz),
            std::make_tuple(sx, sy, sz),
            std::make_tuple(width, height),
            std::make_tuple(cr, cg, cb)
        );
        #ifdef _DEBUG
            std::cout << "Plane: "
                "axis=" << axis << ", "
                "positionx=" << x << ", "
                "positiony=" << y << ", "
                "positionz=" << z << ", "
                "color(" << cr << ", " << cg << ", " << cb << ")"
                << std::endl;
        #endif
    }

    return planesVector;
}

std::vector<cylinder_t> Parser::_getCylindersData(const libconfig::Setting &root)
{
    std::vector<cylinder_t> cylinderVector;

    const auto &cylinder = root["primitives"]["cylinders"];

    for (int i = 0; i < cylinder.getLength(); ++i) {
        const auto &s = cylinder[i];
        const auto &position = s["position"];
        const auto &rotation = s["rotation"];
        const auto &scale = s["scale"];
        const auto &color = s["color"];
        double px = position["x"];
        double py = position["y"];
        double pz = position["z"];
        double rx = rotation["x"];
        double ry = rotation["y"];
        double rz = rotation["z"];
        double sx = scale["x"];
        double sy = scale["y"];
        double sz = scale["z"];
        double radius = s["r"];
        double height = s["h"];
        int cr = color["r"];
        int cg = color["g"];
        int cb = color["b"];
        cylinderVector.emplace_back(
            std::make_tuple(px, py, pz, radius, height),
            std::make_tuple(rx, ry, rz),
            std::make_tuple(sx, sy, sz),
            std::make_tuple(cr, cg, cb)
        );
        #ifdef _DEBUG
            std::cout << "Cylinder: "
                "pos(" << px << ", " << py << ", " << pz << "), "
                "r=" << radius << ", "
                "h=" << height << ", "
                "color(" << cr << ", " << cg << ", " << cb << ")"
                << std::endl;
        #endif
    }

    return cylinderVector;
}

std::vector<cone_t> Parser::_getConesData(const libconfig::Setting &root)
{
    std::vector<cone_t> coneVector;

    try {
        const auto &cone = root["primitives"]["cones"];

        for (int i = 0; i < cone.getLength(); ++i) {
            const auto &s = cone[i];
            const auto &position = s["position"];
            const auto &rotation = s["rotation"];
            const auto &scale = s["scale"];
            const auto &color = s["color"];
            double px = position["x"];
            double py = position["y"];
            double pz = position["z"];
            double rx = rotation["x"];
            double ry = rotation["y"];
            double rz = rotation["z"];
            double sx = scale["x"];
            double sy = scale["y"];
            double sz = scale["z"];
            double radius = s["r"];
            double height = s["h"];
            int cr = color["r"];
            int cg = color["g"];
            int cb = color["b"];
            coneVector.emplace_back(
                std::make_tuple(px, py, pz, radius, height),
                std::make_tuple(rx, ry, rz),
                std::make_tuple(sx, sy, sz),
                std::make_tuple(cr, cg, cb)
            );
            #ifdef _DEBUG
                std::cout << "Cone: "
                    "pos(" << px << ", " << py << ", " << pz << "), "
                    "r=" << radius << ", "
                    "h=" << height << ", "
                    "color(" << cr << ", " << cg << ", " << cb << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No cones found in config" << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Cone setting type error: " << e.what() << std::endl;
    }

    return coneVector;
}

std::vector<torus_t> Parser::_getTorusData(const libconfig::Setting &root)
{
    std::vector<torus_t> torusVector;

    try {
        const auto &torus = root["primitives"]["toruses"];

        for (int i = 0; i < torus.getLength(); ++i) {
            const auto &s = torus[i];
            const auto &pos = s["position"];
            const auto &rota = s["rotation"];
            const auto &scale = s["scale"];
            const auto &color = s["color"];
            double px = pos["x"];
            double py = pos["y"];
            double pz = pos["z"];
            double rx = rota["x"];
            double ry = rota["y"];
            double rz = rota["z"];
            double sx = scale["x"];
            double sy = scale["y"];
            double sz = scale["z"];
            double majorRadius = s["R"];
            double minorRadius = s["r"];
            int cr = color["r"], cg = color["g"], cb = color["b"];
            torusVector.emplace_back(
                std::make_tuple(px, py, pz, majorRadius, minorRadius),
                std::make_tuple(rx, ry, rz),
                std::make_tuple(sx, sy, sz),
                std::make_tuple(cr, cg, cb)
            );
            #ifdef _DEBUG
                std::cout << "Torus: "
                    "pos(" << px << ", " << py << ", " << pz << "), "
                    "R=" << majorRadius << ", "
                    "r=" << minorRadius << ", "
                    "color(" << cr << ", " << cg << ", " << cb << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No toruses found in config" << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Torus setting type error: " << e.what() << std::endl;
    }

    return torusVector;
}

std::vector<tanglecube_t> Parser::_getTanglecubesData(const libconfig::Setting &root)
{
    std::vector<tanglecube_t> tangleCubeVector;
    try {
        const auto &tanglecube = root["primitives"]["tanglecubes"];

        for (int i = 0; i < tanglecube.getLength(); ++i) {
            const auto &s = tanglecube[i];
            const auto &pos = s["position"];
            const auto &rota = s["rotation"];
            const auto &scale = s["scale"];
            const auto &color = s["color"];
            double size = s["size"];
            double px = pos["x"];
            double py = pos["y"];
            double pz = pos["z"];
            double rx = rota["x"];
            double ry = rota["y"];
            double rz = rota["z"];
            double sx = scale["x"];
            double sy = scale["y"];
            double sz = scale["z"];
            int cr = color["r"];
            int cg = color["g"];
            int cb = color["b"];
            tangleCubeVector.emplace_back(
                std::make_tuple(px, py, pz, size),
                std::make_tuple(rx, ry, rz),
                std::make_tuple(sx, sy, sz),
                std::make_tuple(cr, cg, cb)
            );
            #ifdef _DEBUG
                std::cout << "Tanglecube: "
                    "pos(" << px << ", " << py << ", " << pz << "), "
                    "size=" << size << ", "
                    "color(" << cr << ", " << cg << ", " << cb << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No tanglecubes found in config" << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Tanglecube setting type error: " << e.what() << std::endl;
    }

    return tangleCubeVector;
}

std::vector<triangle_t> Parser::_getTrianglesData(const libconfig::Setting &root)
{
    std::vector<triangle_t> triangleVector;

    try {
        const auto &triangles = root["primitives"]["triangles"];

        for (int i = 0; i < triangles.getLength(); ++i) {
            const auto &t = triangles[i];
            const auto &p1 = t["p1"];
            const auto &p2 = t["p2"];
            const auto &p3 = t["p3"];
            const auto &rotation = t["rotation"];
            const auto &scale = t["scale"];
            const auto &color = t["color"];
            double p1x = p1["x"];
            double p1y = p1["y"];
            double p1z = p1["z"];
            double p2x = p2["x"];
            double p2y = p2["y"];
            double p2z = p2["z"];
            double p3x = p3["x"];
            double p3y = p3["y"];
            double p3z = p3["z"];
            double rx = rotation["x"];
            double ry = rotation["y"];
            double rz = rotation["z"];
            double sx = scale["x"];
            double sy = scale["y"];
            double sz = scale["z"];
            int cr = color["r"];
            int cg = color["g"];
            int cb = color["b"];
            triangleVector.emplace_back(
                std::make_tuple(
                    std::make_tuple(p1x, p1y, p1z),
                    std::make_tuple(p2x, p2y, p2z),
                    std::make_tuple(p3x, p3y, p3z)
                ),
                std::make_tuple(rx, ry, rz),
                std::make_tuple(sx, sy, sz),
                std::make_tuple(cr, cg, cb)
            );
            #ifdef _DEBUG
                std::cout << "Triangle: "
                    "p1(" << p1x << "," << p1y << "," << p1z << "), "
                    "p2(" << p2x << "," << p2y << "," << p2z << "), "
                    "p3(" << p3x << "," << p3y << "," << p3z << "), "
                    "color(" << cr << "," << cg << "," << cb << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No triangles found in config" << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Triangle setting type error: " << e.what() << std::endl;
    }

    return triangleVector;
}

std::vector<obj_t> Parser::_getOBJsData(const libconfig::Setting &root)
{
    std::vector<obj_t> objVector;

    try {
        const auto &objs = root["primitives"]["objs"];

        for (int i = 0; i < objs.getLength(); ++i) {
            const auto &o = objs[i];
            const auto &pos = o["position"];
            const auto &rota = o["rotation"];
            const auto &scale = o["scale"];
            const auto &color = o["color"];
            std::string filepath = o["filepath"].c_str();
            double px = pos["x"];
            double py = pos["y"];
            double pz = pos["z"];
            double rx = rota["x"];
            double ry = rota["y"];
            double rz = rota["z"];
            double sx = scale["x"];
            double sy = scale["y"];
            double sz = scale["z"];
            int cr = color["r"];
            int cg = color["g"];
            int cb = color["b"];
            objVector.emplace_back(
                std::make_tuple(px, py, pz, filepath),
                std::make_tuple(rx, ry, rz),
                std::make_tuple(sx, sy, sz),
                std::make_tuple(cr, cg, cb)
            );
            #ifdef _DEBUG
                std::cout << "OBJ: "
                    "pos(" << px << ", " << py << ", " << pz << "), "
                    "filepath=" << filepath << ", "
                    "color(" << cr << ", " << cg << ", " << cb << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No OBJ files found in config" << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] OBJ setting type error: " << e.what() << std::endl;
    }

    return objVector;
}

std::vector<fractalecube_t> Parser::_getFractaleCubesData(const libconfig::Setting &root)
{
    std::vector<fractalecube_t> fractaleCubeVector;
    try {
        const auto &fractalecubes = root["primitives"]["fractalecubes"];
        for (int i = 0; i < fractalecubes.getLength(); ++i) {
            const auto &s = fractalecubes[i];
            const auto &pos = s["position"];
            const auto &rota = s["rotation"];
            const auto &scale = s["scale"];
            const auto &color = s["color"];
            double px = pos["x"];
            double py = pos["y"];
            double pz = pos["z"];
            double size = s["size"];
            double rx = rota["x"];
            double ry = rota["y"];
            double rz = rota["z"];
            double sx = scale["x"];
            double sy = scale["y"];
            double sz = scale["z"];
            int cr = color["r"];
            int cg = color["g"];
            int cb = color["b"];
            fractaleCubeVector.emplace_back(
                std::make_tuple(px, py, pz, size),
                std::make_tuple(rx, ry, rz),
                std::make_tuple(sx, sy, sz),
                std::make_tuple(cr, cg, cb)
            );
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No fractalecubes found in config" << std::endl;
        #endif
    }
    return fractaleCubeVector;
}

void Parser::_getPrimitivesData(const libconfig::Setting &root)
{
    std::vector<sphere_t> spheresVector = _getSpheresData(root);

    std::vector<plane_t> planesVector = _getPlanesData(root);

    std::vector<cylinder_t> cylinderVector = _getCylindersData(root);

    std::vector<cone_t> coneVector = _getConesData(root);

    std::vector<torus_t> torusVector = _getTorusData(root);

    std::vector<tanglecube_t> tangleCubeVector = _getTanglecubesData(root);

    std::vector<triangle_t> triangleVector = _getTrianglesData(root);

    std::vector<obj_t> objVector = _getOBJsData(root);

    std::vector<fractalecube_t> fractaleCubeVector = _getFractaleCubesData(root);

    this->_primitiveConfig = std::make_unique<PrimitivesConfig>(
        spheresVector,
        planesVector,
        cylinderVector,
        coneVector,
        torusVector,
        tangleCubeVector,
        triangleVector,
        objVector,
        fractaleCubeVector
    );
}

ambient_t Parser::_getAmbientData(const libconfig::Setting &root)
{
    ambient_t ambientData;

    try {
        const auto &ambient = root["lights"]["ambient"];
        const auto &s = ambient[0];
        const auto &color = s["color"];
        double intensity = s["intensity"];
        int cr = color["r"];
        int cg = color["g"];
        int cb = color["b"];
        ambientData = std::make_tuple(intensity, std::make_tuple(cr, cg, cb));
        #ifdef _DEBUG
            std::cout << "Ambient Light: intensity= "<< intensity
                      << ", color(" << cr << ", " << cg << ", " << cb << ")" << std::endl;
        #endif
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[WARNING] Ambient light not found in config" << std::endl;
        ambientData = std::make_tuple(0.0, std::make_tuple(0, 0, 0));
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Ambient light setting type error: " << e.what() << std::endl;
        ambientData = std::make_tuple(0.0, std::make_tuple(0, 0, 0));
    }
    return ambientData;
}

std::vector<directional_t> Parser::_getDirectionalData(const libconfig::Setting &root)
{
    std::vector<directional_t> directionalData;
    const auto &directional = root["lights"]["directional"];

    for (int i = 0; i < directional.getLength(); ++i) {
        const auto &s = directional[i];
        double intensity = s["intensity"];
        const auto &direction = s["direction"];
        const auto &position = s["position"];
        const auto &color = s["color"];
        double dx = direction["x"];
        double dy = direction["y"];
        double dz = direction["z"];
        double px = position["x"];
        double py = position["y"];
        double pz = position["z"];
        int cr = color["r"];
        int cg = color["g"];
        int cb = color["b"];
        directionalData.emplace_back(
            intensity,
            std::make_tuple(px, py, pz),
            std::make_tuple(dx, dy, dz),
            std::make_tuple(cr, cg, cb)
        );
        #ifdef _DEBUG
            std::cout << "Directional Light " << i << ": intensity= "<< intensity
                    << ", direction(" << dx << ", " << dy << ", " << dz << ")"
                    << ", position(" << px << ", " << py << ", " << pz << ")"
                    << ", color(" << cr << ", " << cg << ", " << cb << ")" << std::endl;
        #endif
    }
    return directionalData;
}

void Parser::_getLightsData(const libconfig::Setting &root)
{
    auto ambient = this->_getAmbientData(root);
    auto directional = this->_getDirectionalData(root);
    this->_lightConfig = std::make_unique<LightsConfig>(ambient, directional);
}

CameraConfig Parser::getCameraConfig() const
{
    return *this->_camConfig;
}

LightsConfig Parser::getLightConfig() const
{
    return *this->_lightConfig;
}

PrimitivesConfig Parser::getPrimitivesConfig() const
{
    return *this->_primitiveConfig;
}

Parser::Parser(char *path)
{
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
        #ifdef _DEBUG
            std::cout << "Parsing ["<< path <<"]" << std::endl;
        #endif
        this->_getCameraData(root);
        this->_getLightsData(root);
        this->_getPrimitivesData(root);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[ERROR] Missing setting: " << e.getPath() << "\n";
        throw;
    }
}

}
