//
// Created by roussierenoa on 4/28/25.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>
#include <chrono>
#include <atomic>

#include "Core/Core.hpp"
#include "Graphic/Camera.hpp"
#include "Parser/Parser.hpp"
#include "Core/Renderer.hpp"
#include "GraphicRenderer/GraphicRenderer.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./raytracer <config_file.cfg>" << std::endl;
        return 84;
    }

    try {
        RayTracer::Core core(av);
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
