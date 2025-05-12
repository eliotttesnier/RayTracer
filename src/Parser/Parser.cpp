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
    auto resolution = this->_getData2D<int>(camera["resolution"], "width", "height");
    auto position = this->_getData3D<double>(camera["position"]);
    auto rotation = this->_getData3D<double>(camera["rotation"]);
    double fov = camera["fieldOfView"];
    #ifdef _DEBUG
        std::cout << "Camera: " << std::get<0>(resolution) << "x" << std::get<1>(resolution) << ", "
            << "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
            << "rota(" <<  std::get<0>(rotation) << ", " << std::get<1>(rotation) << ", " <<  std::get<2>(rotation) << "), "
            << "fov(" << fov << ")" << std::endl;
    #endif
    this->_camConfig = std::make_unique<CameraConfig>(
        resolution,
        position,
        rotation,
        fov
    );
}

std::vector<sphere_t> Parser::_getSpheresData(const libconfig::Setting &root)
{
    std::vector<sphere_t> spheresVector;
    const auto &spheres = root["primitives"]["spheres"];
    for (int i = 0; i < spheres.getLength(); ++i) {
        const auto &s = spheres[i];
        material_t material = this->_getData3D<double>(s,"transparency", "reflection", "refraction");
        auto position = this->_getData3D<double>(s["position"]);
        auto rotation = this->_getData3D<double>(s["rotation"]);
        auto scl = this->_getData3D<double>(s["scale"]);
        auto shear = this->_getData3D<double>(s["shear"]);
        auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
        double radius = s["r"];
        spheresVector.emplace_back(
            material,
            radius,
            position,
            rotation,
            scl,
            shear,
            color
        );
        #ifdef _DEBUG
            std::cout << "Sphere: pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
                << "r=" << radius << ", "
                << "rota(" <<  std::get<0>(rotation) << ", " << std::get<1>(rotation) << ", " <<  std::get<2>(rotation) << "), "
                << "color(" <<  std::get<0>(color) << ", " << std::get<1>(color) << ", " <<  std::get<2>(color) <<  ")\n";
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
        material_t material = this->_getData3D<double>(p, "transparency", "reflection", "refraction");
        auto position = this->_getData3D<double>(p["position"]);
        auto rotation = this->_getData3D<double>(p["rotation"]);
        auto scale = this->_getData3D<double>(p["scale"]);
        auto shear = this->_getData3D<double>(p["shear"]);
        auto color = this->_getData3D<int>(p["color"], "r", "g", "b");
        std::string axis = p["axis"];
        planesVector.emplace_back(
            material,
            axis[0],
            position,
            rotation,
            scale,
            shear,
            color
        );
        #ifdef _DEBUG
            std::cout << "Plane: "
                "axis=" << axis << ", "
                "position("  << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
                "rotation("  << std::get<0>(rotation) << ", " <<  std::get<1>(rotation) << ", " << std::get<2>(rotation) << "), "
                "color("  << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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
        material_t material = this->_getData3D<double>(s, "transparency", "reflection", "refraction");
        auto position = this->_getData3D<double>(s["position"]);
        auto rotation = this->_getData3D<double>(s["rotation"]);
        auto scale = this->_getData3D<double>(s["scale"]);
        auto shear = this->_getData3D<double>(s["shear"]);
        auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
        auto size = this->_getData2D<double>(s, "r", "h");
        cylinderVector.emplace_back(
            material,
            size,
            position,
            rotation,
            scale,
            shear,
            color
        );
        #ifdef _DEBUG
            std::cout << "Cylinder: "
                "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
                "r=" << std::get<0>(size) << ", "
                "h=" << std::get<1>(size) << ", "
                "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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
            material_t material = this->_getData3D<double>(s, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>(s["position"]);
            auto rotation = this->_getData3D<double>(s["rotation"]);
            auto scale = this->_getData3D<double>(s["scale"]);
            auto shear = this->_getData3D<double>(s["shear"]);
            auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
            auto size = this->_getData2D<double>(s, "r", "h");
            coneVector.emplace_back(
                material,
                size,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Cone: "
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
                    "r=" << std::get<0>(size) << ", "
                    "h=" << std::get<1>(size) << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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
            material_t material = this->_getData3D<double>(s, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>(s["position"]);
            auto rotation = this->_getData3D<double>(s["rotation"]);
            auto scale = this->_getData3D<double>(s["scale"]);
            auto shear = this->_getData3D<double>(s["shear"]);
            auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
            auto size = this->_getData2D<double>(s, "R", "r");
            torusVector.emplace_back(
                material,
                size,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Torus: "
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
                    "R=" << std::get<0>(size) << ", "
                    "r=" << std::get<1>(size) << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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
            material_t material = this->_getData3D<double>(s, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>( s["position"]);
            auto rotation = this->_getData3D<double>(s["rotation"]);
            auto scale = this->_getData3D<double>(s["scale"]);
            auto shear = this->_getData3D<double>(s["shear"]);
            auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
            double size = s["size"];
            tangleCubeVector.emplace_back(
                material,
                size,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Tanglecube: "
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) <<  "), "
                    "size=" << size << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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

std::vector<fractalecube_t> Parser::_getFractaleCubesData(const libconfig::Setting &root)
{
    std::vector<fractalecube_t> fractaleCubeVector;
    try {
        const auto &fractalecubes = root["primitives"]["fractalecubes"];
        for (int i = 0; i < fractalecubes.getLength(); ++i) {
            const auto &s = fractalecubes[i];
            material_t material = this->_getData3D<double>(s, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>(s["position"]);
            auto rotation = this->_getData3D<double>(s["rotation"]);
            auto scale = this->_getData3D<double>(s["scale"]);
            auto shear = this->_getData3D<double>(s["shear"]);
            auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
            double size = s["size"];
            int recursion = s["recursion"];
            fractaleCubeVector.emplace_back(
                material,
                size,
                recursion,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "FractaleCube: "
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " << std::get<2>(position) << "), "
                    "size=" << size << ", "
                    "recursion=" << recursion << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No fractalecubes found in config" << std::endl;
        #endif
    }
    return fractaleCubeVector;
}

std::vector<triangle_t> Parser::_getTrianglesData(const libconfig::Setting &root)
{
    std::vector<triangle_t> triangleVector;

    try {
        const auto &triangles = root["primitives"]["triangles"];

        for (int i = 0; i < triangles.getLength(); ++i) {
            const auto &t = triangles[i];
            material_t material = this->_getData3D<double>(t, "transparency", "reflection", "refraction");
            auto p1 = this->_getData3D<double>(t["p1"]);
            auto p2 = this->_getData3D<double>(t["p2"]);
            auto p3 = this->_getData3D<double>(t["p3"]);
            auto rotation = this->_getData3D<double>(t["rotation"]);
            auto scale = this->_getData3D<double>(t["scale"]);
            auto shear = this->_getData3D<double>(t["shear"]);
            auto color = this->_getData3D<int>(t["color"], "r", "g", "b");
            triangleVector.emplace_back(
                material,
                std::make_tuple(
                    p1,
                    p2,
                    p3
                ),
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Triangle: "
                    "p1(" << std::get<0>(p1) << "," << std::get<1>(p1) << "," << std::get<2>(p1) << "), "
                    "p2(" << std::get<0>(p2) << "," << std::get<1>(p2) << "," << std::get<2>(p2) << "), "
                    "p3(" << std::get<0>(p3) << "," << std::get<1>(p3) << "," << std::get<2>(p3) << "), "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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
            material_t material = this->_getData3D<double>(o, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>(o["position"]);
            auto rotation = this->_getData3D<double>(o["rotation"]);
            auto scale = this->_getData3D<double>(o["scale"]);
            auto shear = this->_getData3D<double>(o["shear"]);
            auto color = this->_getData3D<int>(o["color"], "r", "g", "b");
            std::string filepath = o["filepath"].c_str();

            objVector.emplace_back(
                material,
                filepath,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "OBJ: "
                    "pos(" << std::get<0>(position) << "," << std::get<1>(position) << "," << std::get<2>(position) << "), "
                    "filepath=" << filepath << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
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

std::vector<infinitecylinder_t> Parser::_getInfiniteCylindersData(
    const libconfig::Setting &root
)
{
    std::vector<infinitecylinder_t> infiniteCylinderVector;
    try {
        const auto &infiniteCylinders = root["primitives"]["infiniteCylinders"];
        for (int i = 0; i < infiniteCylinders.getLength(); ++i) {
            const auto &c = infiniteCylinders[i];
            material_t material = this->_getData3D<double>(c, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>(c["position"]);
            auto rotation = this->_getData3D<double>(c["rotation"]);
            auto scale = this->_getData3D<double>(c["scale"]);
            auto shear = this->_getData3D<double>(c["shear"]);
            auto color = this->_getData3D<int>(c["color"], "r", "g", "b");
            double radius = c["r"];
            infiniteCylinderVector.emplace_back(
                material,
                radius,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Infinite Cylinder: "
                    << "pos(" << std::get<0>(position) << "," << std::get<1>(position) << "," << std::get<2>(position) << "), "
                    << "r=" << radius << ", "
                    << "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No infinite cylinders found in config" << std::endl;
        #endif
    }
    return infiniteCylinderVector;
}

std::vector<infinitecone_t> Parser::_getInfiniteConesData(const libconfig::Setting &root)
{
    std::vector<infinitecone_t> infiniteConeVector;
    try {
        const auto &infiniteCones = root["primitives"]["infiniteCones"];
        for (int i = 0; i < infiniteCones.getLength(); ++i) {
            const auto &c = infiniteCones[i];
            material_t material = this->_getData3D<double>(c, "transparency", "reflection", "refraction");
            auto position = this->_getData3D<double>(c["position"]);
            auto rotation = this->_getData3D<double>(c["rotation"]);
            auto scale = this->_getData3D<double>(c["scale"]);
            auto shear = this->_getData3D<double>(c["shear"]);
            auto color = this->_getData3D<int>(c["color"], "r", "g", "b");
            double angle = c["angle"];
            infiniteConeVector.emplace_back(
                material,
                angle,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Infinite Cone: "
                    << "pos(" << std::get<0>(position) << "," << std::get<1>(position) << "," << std::get<2>(position) << "), "
                    << "angle=" << angle << ", "
                    << "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")"
                    << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No infinite cones found in config" << std::endl;
        #endif
    }
    return infiniteConeVector;
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

    std::vector<infinitecylinder_t> infiniteCylinders = _getInfiniteCylindersData(root);

    std::vector<infinitecone_t> infiniteCones = _getInfiniteConesData(root);

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
        infiniteCylinders,
        infiniteCones,
        fractaleCubeVector
    );
}

ambient_t Parser::_getAmbientData(const libconfig::Setting &root)
{
    ambient_t ambientData;

    try {
        const auto &s = root["lights"]["ambient"];
        auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
        double intensity = s["intensity"];
        ambientData = std::make_tuple(intensity, color);
        #ifdef _DEBUG
            std::cout << "Ambient Light: intensity= "<< intensity
                      << ", color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " << std::get<2>(color) << ")" << std::endl;
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
        auto direction = this->_getData3D<double>(s["direction"]);
        auto position = this->_getData3D<double>(s["position"]);
        auto color = this->_getData3D<int>(s["color"], "r", "g", "b");
        double intensity = s["intensity"];
        directionalData.emplace_back(
            intensity,
            position,
            direction,
            color
        );
        #ifdef _DEBUG
            std::cout << "Directional Light " << i << ": intensity= "<< intensity
                    << ", direction(" << std::get<0>(direction) << ", " << std::get<1>(direction) << ", " << std::get<2>(direction) << ")"
                    << ", position(" << std::get<0>(position) << ", " << std::get<1>(position) << ", " << std::get<2>(position) << ")"
                    << ", color(" << std::get<0>(color) << ", " << std::get<1>(color) << ", " << std::get<2>(color) << ")" << std::endl;
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

void Parser::_importScenes(const libconfig::Setting &root)
{
    if (!root.exists("scenes")) {
        #ifdef _DEBUG
            std::cout << "No scenes to import" << std::endl;
        #endif
        return;
    }

    try {
        const auto &scenes = root["scenes"];

        for (int i = 0; i < scenes.getLength(); ++i) {
            const auto &scene = scenes[i];
            std::string filepath = scene.c_str();
            _importScene(filepath, const_cast<libconfig::Setting &>(root));
        }
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Scenes setting type error: " << e.what() << std::endl;
    }
}

void Parser::_importScene(const std::string &filepath, libconfig::Setting &targetRoot)
{
    if (_importedScenes.find(filepath) != _importedScenes.end()) {
        #ifdef _DEBUG
            std::cout << "Scene already imported: " << filepath
                << ". Skipping to avoid cycles." << std::endl;
        #endif
        return;
    }
    #ifdef _DEBUG
        std::cout << "Importing scene: " << filepath << std::endl;
    #endif
    _importedScenes.insert(filepath);
    libconfig::Config import_cfg;
    try {
        import_cfg.readFile(filepath.c_str());
        const libconfig::Setting &import_root = import_cfg.getRoot();

        _importPrimitives(import_root, targetRoot);
        _importLights(import_root, targetRoot);
        if (import_root.exists("scenes")) {
            const auto &scenes = import_root["scenes"];
            for (int i = 0; i < scenes.getLength(); ++i) {
                const auto &scene = scenes[i];
                std::string nestedFilepath = scene.c_str();
                _importScene(nestedFilepath, targetRoot);
            }
        }
    } catch (const libconfig::FileIOException &e) {
        std::cerr << "[ERROR] I/O error while reading imported scene file: "
            << filepath << std::endl;
    } catch (const libconfig::ParseException &e) {
        std::cerr << "[ERROR] Parse error in imported scene at " << e.getFile()
            << ":" << e.getLine() << " - " << e.getError() << std::endl;
    }
}

void Parser::_importPrimitives(const libconfig::Setting &sourceRoot,
libconfig::Setting &targetRoot)
{
    try {
        if (!sourceRoot.exists("primitives"))
            return;

        const auto &sourcePrimitives = sourceRoot["primitives"];
        libconfig::Setting &targetPrimitives = targetRoot["primitives"];

        const char *primitiveTypes[] = {
            "spheres", "planes", "cylinders", "cones",
            "toruses", "tanglecubes", "triangles", "objs"
        };

        for (const char *type : primitiveTypes) {
            if (sourcePrimitives.exists(type) && targetPrimitives.exists(type)) {
                const auto &sourceItems = sourcePrimitives[type];
                libconfig::Setting &targetItems = targetPrimitives[type];
                #ifdef _DEBUG
                    std::cout << "Importing " << sourceItems.getLength()
                        << " " << type << std::endl;
                #endif
                for (int i = 0; i < sourceItems.getLength(); ++i) {
                    const auto &sourceItem = sourceItems[i];
                    libconfig::Setting &newItem =
                        targetItems.add(libconfig::Setting::TypeGroup);
                    _copySettings(sourceItem, newItem);
                }
            }
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[WARNING] Element not found during primitives import: "
            << e.getPath() << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Setting type error during primitives import: "
            << e.what() << std::endl;
    }
}

void Parser::_importLights(const libconfig::Setting &sourceRoot,
libconfig::Setting &targetRoot)
{
    try {
        if (!sourceRoot.exists("lights"))
            return;

        const auto &sourceLights = sourceRoot["lights"];
        libconfig::Setting &targetLights = targetRoot["lights"];

        if (sourceLights.exists("directional") && targetLights.exists("directional")) {
            const auto &sourceLightsItems = sourceLights["directional"];
            libconfig::Setting &targetLightsItems = targetLights["directional"];
            #ifdef _DEBUG
                std::cout << "Importing " << sourceLightsItems.getLength() <<
                    " directional lights" << std::endl;
            #endif
            for (int i = 0; i < sourceLightsItems.getLength(); ++i) {
                const auto &sourceItem = sourceLightsItems[i];
                libconfig::Setting &newItem = targetLightsItems.add(
                    libconfig::Setting::TypeGroup
                );
                _copySettings(sourceItem, newItem);
            }
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[WARNING] Element not found during lights import: "
            << e.getPath() << std::endl;
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Setting type error during lights import: "
            << e.what() << std::endl;
    }
}

void Parser::_copySettings(const libconfig::Setting &source, libconfig::Setting &target)
{
    for (int field = 0; field < source.getLength(); ++field) {
        const char *name = source[field].getName();

        if (source[field].isGroup()) {
            libconfig::Setting &group = target.add(name, libconfig::Setting::TypeGroup);
            const auto &sourceGroup = source[field];

            for (int subfield = 0; subfield < sourceGroup.getLength(); ++subfield) {
                const char *subname = sourceGroup[subfield].getName();

                if (sourceGroup[subfield].getType() == libconfig::Setting::TypeInt) {
                    int value = static_cast<int>(sourceGroup[subfield]);
                    group.add(subname, libconfig::Setting::TypeInt) = value;
                } else if (sourceGroup[subfield].getType() == libconfig::Setting::TypeFloat) {
                    double value = static_cast<double>(sourceGroup[subfield]);
                    group.add(subname, libconfig::Setting::TypeFloat) = value;
                } else if (sourceGroup[subfield].isNumber()) {
                    double value = static_cast<double>(sourceGroup[subfield]);
                    group.add(subname, libconfig::Setting::TypeFloat) = value;
                }
            }
        } else if (source[field].getType() == libconfig::Setting::TypeInt) {
            int value = static_cast<int>(source[field]);
            target.add(name, libconfig::Setting::TypeInt) = value;
        } else if (source[field].getType() == libconfig::Setting::TypeFloat) {
            double value = static_cast<double>(source[field]);
            target.add(name, libconfig::Setting::TypeFloat) = value;
        } else if (source[field].isNumber()) {
            double value = static_cast<double>(source[field]);
            target.add(name, libconfig::Setting::TypeFloat) = value;
        } else if (source[field].getType() == libconfig::Setting::TypeString) {
            std::string value = static_cast<const char*>(source[field].c_str());
            target.add(name, libconfig::Setting::TypeString) = value;
        }
    }
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
        this->_importScenes(root);
        this->_getLightsData(root);
        this->_getPrimitivesData(root);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[ERROR] Missing setting: " << e.getPath() << "\n";
        throw;
    }
}

}
