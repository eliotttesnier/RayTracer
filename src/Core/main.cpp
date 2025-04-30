//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>

#include "Primitives/IPrimitive.hpp"
#include "Primitives/Plane/Plane.hpp"
#include "Primitives/Sphere/Sphere.hpp"
#include "Primitives/Cylinder/Cylinder.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Ray.hpp"
#include "Math/Rectangle3D.hpp"
#include "Graphic/Camera.hpp"
#include "Parser/Parser.hpp"
#include "Core/Renderer.hpp"
#include "GraphicRenderer/GraphicRenderer.hpp"

//TODO: À retirer
void displaySphere() {
    const int WIDTH = 3820;
    const int HEIGHT = 2160;
    const double ASPECT_RATIO = static_cast<double>(WIDTH) / HEIGHT;

    RayTracer::Camera camera;
    camera.origin = Math::Point3D(0, 0, 5);
    camera.tilt(-10);

    auto cylinder = std::make_shared<Raytracer::primitive::Cylinder>();
    cylinder->getPosition() = Math::Point3D(0, -1, 0);
    cylinder->setRadius(1.0);
    cylinder->setHeight(2.0);

    auto plane = std::make_shared<Raytracer::primitive::Plane>();
    plane->getPosition() = Math::Point3D(0, -2, 0);
    plane->getRotation() = Math::Vector3D(0, 0, 0);

    std::vector<std::shared_ptr<IPrimitive>> primitives;
    primitives.push_back(cylinder);
    primitives.push_back(plane);

    try {
        Renderer renderer(camera, primitives);
        renderer.setResolution(WIDTH, HEIGHT);
        renderer.setOutputFile("output.ppm");

        std::cout << "Starting rendering..." << std::endl;
        renderer.render();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    try {
        GraphicRenderer graphicRenderer("output.ppm");
        graphicRenderer.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

int main(int ac, char **av) {
    if (ac == 2) {
        try {
            raytracer::Parser::Parser parser = raytracer::Parser::Parser(av[1]);
            displaySphere();
        } catch (const std::exception &e) {
            std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Usage: ./raytracer <config_file.cfg>" << std::endl;
        return 1;
    }
    return 0;
}
