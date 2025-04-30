//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>

#include "../Primitives/IPrimitive.hpp"
#include "../Primitives/Plane/Plane.hpp"
#include "../Primitives/Sphere/Sphere.hpp"
#include "../Math/Point3D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Rectangle3D.hpp"
#include "../Graphic/Camera.hpp"
#include "../GraphicRenderer/GraphicRenderer.hpp"

int main() {
    const int WIDTH = 80;
    const int HEIGHT = 40;
    const double ASPECT_RATIO = static_cast<double>(WIDTH) / HEIGHT;

    RayTracer::Camera camera;
    camera.origin = Math::Point3D(0, 0, 5);
    camera.tilt(-10);

    auto sphere = std::make_shared<Raytracer::primitive::Sphere>();
    sphere->getPosition() = Math::Point3D(0, -1, 0);

    auto plane = std::make_shared<Raytracer::primitive::Plane>();
    plane->getPosition() = Math::Point3D(0, -2, 0);

    std::vector<std::shared_ptr<IPrimitive>> primitives;
    primitives.push_back(sphere);
    primitives.push_back(plane);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double u = static_cast<double>(x) / (WIDTH - 1);
            double v = static_cast<double>(y) / (HEIGHT - 1);

            u = u * 2.0 - 1.0;
            v = 1.0 - v * 2.0;
            u *= ASPECT_RATIO;

            Math::Ray ray = camera.ray(u, v);

            double closestDist = std::numeric_limits<double>::max();
            bool hit = false;

            for (const auto& primitive : primitives) {
                Math::hitdata_t hitData = primitive->intersect(ray);

                if (hitData.hit && hitData.distance < closestDist) {
                    closestDist = hitData.distance;
                    hit = true;
                }
            }

            if (hit) {
                std::cout << "@@";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

    try {
        GraphicRenderer renderer("output.ppm");
        renderer.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
