// je
// Created by roussierenoa on 5/12/25.
//

#include <string>
#include <vector>
#include <iostream>
#include "PrimitivesParser.hpp"

#include "Parser.hpp"

namespace RayTracer::Parser
{

std::vector<RayTracer::Parser::sphere_t> PrimitivesParser::getSpheresData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<sphere_t> spheresVector;
    const auto &spheres = root["primitives"]["spheres"];
    for (int i = 0; i < spheres.getLength(); ++i) {
        const auto &s = spheres[i];
        material_t material = RayTracer::Parser::Parser::getMaterialData(s);
        auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
        auto rotation = RayTracer::Parser::Parser::getData3D<double>(s["rotation"]);
        auto scl = RayTracer::Parser::Parser::getData3D<double>(s["scale"]);
        auto shear = RayTracer::Parser::Parser::getData3D<double>(s["shear"]);
        auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
        double radius = s["r"];
        spheresVector.emplace_back(
            shading,
            material,
            radius,
            position,
            rotation,
            scl,
            shear,
            color
        );
        #ifdef _DEBUG
            std::cout << "Sphere: pos(" << std::get<0>(position) << ", " <<
                std::get<1>(position) << ", " << std::get<2>(position) << "), " << "r=" <<
                radius << ", " << "rota(" <<  std::get<0>(rotation) << ", " <<
                std::get<1>(rotation) << ", " <<  std::get<2>(rotation) << "), " << "color("
                <<  std::get<0>(color) << ", " << std::get<1>(color) << ", " <<
                std::get<2>(color) <<  ")" << std::endl;
        #endif
    }
    return spheresVector;
}

std::vector<RayTracer::Parser::plane_t> PrimitivesParser::getPlanesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<plane_t> planesVector;
    const auto &planes = root["primitives"]["planes"];
    for (int i = 0; i < planes.getLength(); ++i) {
        const auto &p = planes[i];
        material_t material = RayTracer::Parser::Parser::getMaterialData(p);
        auto position = RayTracer::Parser::Parser::getData3D<double>(p["position"]);
        auto rotation = RayTracer::Parser::Parser::getData3D<double>(p["rotation"]);
        auto scale = RayTracer::Parser::Parser::getData3D<double>(p["scale"]);
        auto shear = RayTracer::Parser::Parser::getData3D<double>(p["shear"]);
        auto color = RayTracer::Parser::Parser::getData3D<int>(p["color"], "r", "g", "b");
        std::string axis = p["axis"];
        planesVector.emplace_back(
            shading,
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
                "position("  << std::get<0>(position) << ", " <<  std::get<1>(position) <<
                ", " << std::get<2>(position) << "), rotation("  << std::get<0>(rotation)
                << ", " <<  std::get<1>(rotation) << ", " << std::get<2>(rotation) << "), "
                "color("  << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                << std::get<2>(color) << ")" << std::endl;
        #endif
    }
    return planesVector;
}

std::vector<RayTracer::Parser::cylinder_t> PrimitivesParser::getCylindersData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<cylinder_t> cylinderVector;

    const auto &cylinder = root["primitives"]["cylinders"];

    for (int i = 0; i < cylinder.getLength(); ++i) {
        const auto &s = cylinder[i];
        material_t material = RayTracer::Parser::Parser::getMaterialData(s);
        auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
        auto rotation = RayTracer::Parser::Parser::getData3D<double>(s["rotation"]);
        auto scale = RayTracer::Parser::Parser::getData3D<double>(s["scale"]);
        auto shear = RayTracer::Parser::Parser::getData3D<double>(s["shear"]);
        auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
        auto size = RayTracer::Parser::Parser::getData2D<double>(s, "r", "h");
        cylinderVector.emplace_back(
            shading,
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
                "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", " <<
                std::get<2>(position) << "), r=" << std::get<0>(size) << ", "
                "h=" << std::get<1>(size) << ", "
                "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " <<
                std::get<2>(color) << ")"<< std::endl;
        #endif
    }

    return cylinderVector;
}

std::vector<RayTracer::Parser::cone_t> PrimitivesParser::getConesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<cone_t> coneVector;

    try {
        const auto &cone = root["primitives"]["cones"];

        for (int i = 0; i < cone.getLength(); ++i) {
            const auto &s = cone[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(s);
            auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(s["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(s["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(s["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
            auto size = RayTracer::Parser::Parser::getData2D<double>(s, "r", "h");
            coneVector.emplace_back(
                shading,
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
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) <<
                    ", " << std::get<2>(position) << "), r=" << std::get<0>(size) << ", "
                    "h=" << std::get<1>(size) << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                    << std::get<2>(color) << ")"<< std::endl;
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

std::vector<RayTracer::Parser::torus_t> PrimitivesParser::getTorusData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<torus_t> torusVector;

    try {
        const auto &torus = root["primitives"]["toruses"];

        for (int i = 0; i < torus.getLength(); ++i) {
            const auto &s = torus[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(s);
            auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(s["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(s["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(s["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
            auto size = RayTracer::Parser::Parser::getData2D<double>(s, "R", "r");
            torusVector.emplace_back(
                shading,
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
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", "
                    << std::get<2>(position) << "), R=" << std::get<0>(size) << ", "
                    "r=" << std::get<1>(size) << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                    << std::get<2>(color) << ")" << std::endl;
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

std::vector<RayTracer::Parser::tanglecube_t> PrimitivesParser::getTangleCubesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<tanglecube_t> tangleCubeVector;
    try {
        const auto &tanglecube = root["primitives"]["tanglecubes"];

        for (int i = 0; i < tanglecube.getLength(); ++i) {
            const auto &s = tanglecube[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(s);
            auto position = RayTracer::Parser::Parser::getData3D<double>( s["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(s["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(s["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(s["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
            double size = s["size"];
            tangleCubeVector.emplace_back(
                shading,
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
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) <<
                        ", " << std::get<2>(position) <<  "), "
                    "size=" << size << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", " <<
                    std::get<2>(color) << ")" << std::endl;
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

std::vector<RayTracer::Parser::fractalecube_t> PrimitivesParser::getFractaleCubesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<fractalecube_t> fractaleCubeVector;
    try {
        const auto &fractalecubes = root["primitives"]["fractalecubes"];
        for (int i = 0; i < fractalecubes.getLength(); ++i) {
            const auto &s = fractalecubes[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(s);
            auto position = RayTracer::Parser::Parser::getData3D<double>(s["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(s["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(s["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(s["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(s["color"], "r", "g", "b");
            double size = s["size"];
            int recursion = s["recursion"];
            fractaleCubeVector.emplace_back(
                shading,
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
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position)
                    << ", " << std::get<2>(position) << "), size=" << size << ", "
                    "recursion=" << recursion << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                    << std::get<2>(color) << ")" << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No fractalecubes found in config" << std::endl;
        #endif
    }
    return fractaleCubeVector;
}

std::vector<RayTracer::Parser::triangle_t> PrimitivesParser::getTrianglesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<triangle_t> triangleVector;

    try {
        const auto &triangles = root["primitives"]["triangles"];

        for (int i = 0; i < triangles.getLength(); ++i) {
            const auto &t = triangles[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(t);
            auto p1 = RayTracer::Parser::Parser::getData3D<double>(t["p1"]);
            auto p2 = RayTracer::Parser::Parser::getData3D<double>(t["p2"]);
            auto p3 = RayTracer::Parser::Parser::getData3D<double>(t["p3"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(t["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(t["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(t["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(t["color"], "r", "g", "b");
            triangleVector.emplace_back(
                shading,
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
                    "p1(" << std::get<0>(p1) << "," << std::get<1>(p1) << ","
                        << std::get<2>(p1) << "), "
                    "p2(" << std::get<0>(p2) << "," << std::get<1>(p2) << ","
                        << std::get<2>(p2) << "), "
                    "p3(" << std::get<0>(p3) << "," << std::get<1>(p3) << ","
                        << std::get<2>(p3) << "), "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                        << std::get<2>(color) << ")" << std::endl;
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

std::vector<RayTracer::Parser::obj_t> PrimitivesParser::getOBJsData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<obj_t> objVector;

    try {
        const auto &objs = root["primitives"]["objs"];

        for (int i = 0; i < objs.getLength(); ++i) {
            const auto &o = objs[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(o);
            auto position = RayTracer::Parser::Parser::getData3D<double>(o["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(o["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(o["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(o["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(o["color"], "r", "g", "b");
            std::string filepath = o["filepath"].c_str();

            objVector.emplace_back(
                shading,
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
                    "pos(" << std::get<0>(position) << "," << std::get<1>(position) <<
                        "," << std::get<2>(position) << "), filepath=" << filepath << ", "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                        << std::get<2>(color) << ")" << std::endl;
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

std::vector<RayTracer::Parser::infinitecylinder_t> PrimitivesParser::getInfiniteCylindersData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<infinitecylinder_t> infiniteCylinderVector;
    try {
        const auto &infiniteCylinders = root["primitives"]["infiniteCylinders"];
        for (int i = 0; i < infiniteCylinders.getLength(); ++i) {
            const auto &c = infiniteCylinders[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(c);
            auto position = RayTracer::Parser::Parser::getData3D<double>(c["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(c["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(c["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(c["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(c["color"], "r", "g", "b");
            double radius = c["r"];
            infiniteCylinderVector.emplace_back(
                shading,
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
                    << "pos(" << std::get<0>(position) << "," << std::get<1>(position)
                        << "," << std::get<2>(position) << "), " << "r=" << radius << ", "
                    << "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                        << std::get<2>(color) << ")" << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No infinite cylinders found in config" << std::endl;
        #endif
    }
    return infiniteCylinderVector;
}

std::vector<RayTracer::Parser::infinitecone_t> PrimitivesParser::getInfiniteConesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<infinitecone_t> infiniteConeVector;
    try {
        const auto &infiniteCones = root["primitives"]["infiniteCones"];
        for (int i = 0; i < infiniteCones.getLength(); ++i) {
            const auto &c = infiniteCones[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(c);
            auto position = RayTracer::Parser::Parser::getData3D<double>(c["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(c["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(c["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(c["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(c["color"], "r", "g", "b");
            double angle = c["angle"];
            infiniteConeVector.emplace_back(
                shading,
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
                    << "pos(" << std::get<0>(position) << "," << std::get<1>(position)
                        << "," << std::get<2>(position) << "), " << "angle=" << angle << ", "
                    << "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) <<
                        ", " << std::get<2>(color) << ")" << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No infinite cones found in config" << std::endl;
        #endif
    }
    return infiniteConeVector;
}

std::vector<RayTracer::Parser::rectangle_t> PrimitivesParser::getRectanglesData(
    const libconfig::Setting &root,
    shading_t shading
)
{
    std::vector<rectangle_t> rectangleVector;
    try {
        const auto &rectangles = root["primitives"]["rectangles"];

        for (int i = 0; i < rectangles.getLength(); ++i) {
            const auto &r = rectangles[i];
            material_t material = RayTracer::Parser::Parser::getMaterialData(r);
            auto position = RayTracer::Parser::Parser::getData3D<double>(r["position"]);
            auto rotation = RayTracer::Parser::Parser::getData3D<double>(r["rotation"]);
            auto scale = RayTracer::Parser::Parser::getData3D<double>(r["scale"]);
            auto shear = RayTracer::Parser::Parser::getData3D<double>(r["shear"]);
            auto color = RayTracer::Parser::Parser::getData3D<int>(r["color"], "r", "g", "b");
            auto dimensions = RayTracer::Parser::Parser::getData3D<double>(
                r,
                "length",
                "width",
                "height"
            );

            rectangleVector.emplace_back(
                shading,
                material,
                dimensions,
                position,
                rotation,
                scale,
                shear,
                color
            );
            #ifdef _DEBUG
                std::cout << "Rectangle: "
                    "pos(" << std::get<0>(position) << ", " <<  std::get<1>(position) << ", "
                    << std::get<2>(position) << "), dimensions("
                    << std::get<0>(dimensions) << ", " << std::get<1>(dimensions) << ", "
                    << std::get<2>(dimensions) << "), "
                    "color(" << std::get<0>(color) << ", " <<  std::get<1>(color) << ", "
                    << std::get<2>(color) << ")" << std::endl;
            #endif
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        #ifdef _DEBUG
            std::cout << "No rectangles found in config" << std::endl;
        #endif
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "[WARNING] Rectangle setting type error: " << e.what() << std::endl;
    }

    return rectangleVector;
}

}
