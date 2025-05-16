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
    auto resolution = this->getData2D<int>(camera["resolution"], "width", "height");
    auto position = this->getData3D<double>(camera["position"]);
    auto rotation = this->getData3D<double>(camera["rotation"]);
    double fov = camera["fieldOfView"];
    #ifdef _DEBUG
        std::cout << "Camera: " << std::get<0>(resolution) << "x" << std::get<1>(resolution)
            << ", " << "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) <<
            ", " << std::get<2>(position) << "), " << "rota(" <<  std::get<0>(rotation) <<
            ", " << std::get<1>(rotation) << ", " <<  std::get<2>(rotation) << "), " <<
            "fov(" << fov << ")" << std::endl;
    #endif
    this->_camConfig = std::make_unique<CameraConfig>(
        resolution,
        position,
        rotation,
        fov
    );
}

material_t Parser::getMaterialData(const libconfig::Setting &setting)
{
    material_t materialProps;

    try {
        if (setting.exists("transparency")) {
            materialProps["transparency"] = static_cast<double>(setting["transparency"]);
        }
        if (setting.exists("reflection")) {
            materialProps["reflection"] = static_cast<double>(setting["reflection"]);
        }
        if (setting.exists("refraction")) {
            materialProps["refraction"] = static_cast<double>(setting["refraction"]);
        }
        if (setting.exists("chess")) {
            materialProps["chess"] = static_cast<bool>(setting["chess"]);
        }
        if (setting.exists("fileTexture")) {
            materialProps["fileTexture"] = static_cast<std::string>(setting["fileTexture"]);
        }
        if (setting.exists("perlinNoise")) {
            materialProps["perlinNoise"] = static_cast<bool>(setting["perlinNoise"]);
        }
        if (setting.exists("normalMap")) {
            materialProps["normalMap"] = static_cast<std::string>(setting["normalMap"]);
        }
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Material setting type error: " << e.what() << std::endl;
    }
    return materialProps;
}


void Parser::_getPrimitivesData(const libconfig::Setting &root, shading_t shading)
{
    std::vector<sphere_t> spheresVector = PrimitivesParser::getSpheresData(root, shading);

    std::vector<plane_t> planesVector = PrimitivesParser::getPlanesData(root, shading);

    std::vector<cylinder_t> cylinderVector = PrimitivesParser::getCylindersData(root, shading);

    std::vector<cone_t> coneVector = PrimitivesParser::getConesData(root, shading);

    std::vector<torus_t> torusVector = PrimitivesParser::getTorusData(root, shading);

    std::vector<tanglecube_t> tangleCubeVector = PrimitivesParser::getTangleCubesData(
        root,
        shading
    );

    std::vector<triangle_t> triangleVector = PrimitivesParser::getTrianglesData(root, shading);

    std::vector<obj_t> objVector = PrimitivesParser::getOBJsData(root, shading);

    std::vector<infinitecylinder_t> infiniteCylinders =
        PrimitivesParser::getInfiniteCylindersData(root, shading);

    std::vector<infinitecone_t> infiniteCones = PrimitivesParser::getInfiniteConesData(
        root,
        shading
    );

    std::vector<fractalecube_t> fractaleCubeVector =
        PrimitivesParser::getFractaleCubesData(root, shading);

    std::vector<rectangle_t> rectangleVector =
        PrimitivesParser::getRectanglesData(root, shading);

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
        fractaleCubeVector,
        rectangleVector
    );
}

void Parser::_getLightsData(const libconfig::Setting &root)
{
    auto ambient = RayTracer::Parser::LightsParser::getAmbientData(root);
    auto directional = RayTracer::Parser::LightsParser::getDirectionalData(root);
    auto point = RayTracer::Parser::LightsParser::getPositionData(root);
    this->_lightConfig = std::make_unique<LightsConfig>(ambient, directional, point);
}

void Parser::_getAntialiasingData(const libconfig::Setting &root)
{
    try {
        if (!root.exists("antialiasing")) {
            this->_antialiasingConfig = std::make_unique<AntialiasingConfig>(
                "none", 4, 0.1
            );
            return;
        }

        const auto &antialiasing = root["antialiasing"];
        std::string type = "none";
        int samples = 4;
        double threshold = 0.1;

        if (antialiasing.exists("type"))
            type = static_cast<const char*>(antialiasing["type"]);

        if (antialiasing.exists("samples"))
            samples = static_cast<int>(antialiasing["samples"]);

        if (antialiasing.exists("treshold"))
            threshold = static_cast<double>(antialiasing["treshold"]);

        #ifdef _DEBUG
            std::cout << "Antialiasing: type=" << type
                      << ", samples=" << samples
                      << ", threshold=" << threshold << std::endl;
        #endif

        this->_antialiasingConfig = std::make_unique<AntialiasingConfig>(
            type, samples, threshold
        );
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Antialiasing setting type error: " << e.what() << std::endl;
        this->_antialiasingConfig = std::make_unique<AntialiasingConfig>(
            "none", 4, 0.1
        );
    }
}

void Parser::_getRenderingData(const libconfig::Setting &root)
{
    try {
        if (!root.exists("rendering")) {
            this->_renderingConfig = std::make_unique<RenderingConfig>("preview", true, 8u);
            return;
        }

        const auto &rendering = root["rendering"];
        std::string type = "preview";
        bool multithreading = true;
        unsigned int maxThreads = 8u;

        if (rendering.exists("type"))
            type = static_cast<const char*>(rendering["type"]);

        if (rendering.exists("multithreading"))
            multithreading = static_cast<bool>(rendering["multithreading"]);

        if (rendering.exists("maxThreads"))
            maxThreads = static_cast<unsigned int>(rendering["maxThreads"]);
        if (maxThreads < 1)
            maxThreads = 1;

        #ifdef _DEBUG
            std::cout << "Rendering: type=" << type
                      << ", multithreading=" << multithreading
                      << ", maxThreads=" << maxThreads << std::endl;
        #endif

        this->_renderingConfig = std::make_unique<RenderingConfig>(
            type, multithreading, maxThreads
        );
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Rendering setting type error: " << e.what() << std::endl;
    }
}

void Parser::_getShadingData(const libconfig::Setting &root)
{
    double ka = 0.3;
    double kd = 0.5;
    double ks = 0.9;
    double s = 32.0;
    int rc = 8;
    double md = 0.5;
    try {
        if (!root.exists("shading")) {
            _shadingData = std::make_tuple(
                (phong_t) {ka, kd, ks, s}, (ambientOcclusion_t) {rc, md}
            );
            return;
        }
        const auto &shading = root["shading"];
        if (shading.exists("phong")) {
            const auto &phong = shading["phong"];

            if (phong.exists("ambientIntensityFactor"))
                ka = static_cast<double>(phong["ambientIntensityFactor"]);
            if (phong.exists("diffuseIntensityFactor"))
                kd = static_cast<double>(phong["diffuseIntensityFactor"]);
            if (phong.exists("specularIntensityFactor"))
                ks = static_cast<double>(phong["specularIntensityFactor"]);
            if (phong.exists("shininess"))
                s = static_cast<double>(phong["shininess"]);
        }

        if (shading.exists("ambientOcclusion")) {
            const auto &ambientOcclusion = shading["ambientOcclusion"];

            if (ambientOcclusion.exists("rayCount"))
                rc = static_cast<int>(ambientOcclusion["rayCount"]);
            if (ambientOcclusion.exists("maxDistance"))
                md = static_cast<double>(ambientOcclusion["maxDistance"]);
        }
        #ifdef _DEBUG
            std::cout << "Shading config: "
                "ambientIntensityFactor= " << ka <<
                "diffuseIntensityFactor= " << kd <<
                "specularIntensityFactor= " << ks <<
                "shininess= " << s <<
                "rayCount= " << rc <<
                "maxDistance= " << md << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Rendering setting type error: " << e.what() << std::endl;
    }
    _shadingData = std::make_tuple(
        (phong_t) {ka, kd, ks, s}, (ambientOcclusion_t) {rc, md}
    );
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
    if (this->_importedScenes.find(filepath) != this->_importedScenes.end()) {
        #ifdef _DEBUG
            std::cout << "Scene already imported: " << filepath
                << ". Skipping to avoid cycles." << std::endl;
        #endif
        return;
    }
    #ifdef _DEBUG
        std::cout << "Importing scene: " << filepath << std::endl;
    #endif
    this->_importedScenes.insert(filepath);
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
            "toruses", "tanglecubes", "triangles", "objs",
            "rectangles"
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
                } else if (sourceGroup[subfield].getType() ==
                    libconfig::Setting::TypeBoolean) {
                    bool value = static_cast<bool>(sourceGroup[subfield]);
                    group.add(subname, libconfig::Setting::TypeBoolean) = value;
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
        } else if (source[field].getType() == libconfig::Setting::TypeBoolean) {
            bool value = static_cast<bool>(source[field]);
            target.add(name, libconfig::Setting::TypeBoolean) = value;
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

AntialiasingConfig Parser::getAntialiasingConfig() const
{
    return *this->_antialiasingConfig;
}

RenderingConfig Parser::getRenderingConfig() const
{
    return *this->_renderingConfig;
}

Parser::Parser(const char *path)
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
        this->_getShadingData(root);
        this->_getPrimitivesData(root, _shadingData);
        this->_getAntialiasingData(root);
        this->_getRenderingData(root);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "[ERROR] Missing setting: " << e.getPath() << "\n";
        throw;
    }
}

}
