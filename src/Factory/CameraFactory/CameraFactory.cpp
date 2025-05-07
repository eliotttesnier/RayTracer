//
// Created by roussierenoa on 5/1/25.
//

#include "CameraFactory.hpp"
#include <iostream>

std::shared_ptr<RayTracer::Camera> RayTracer::Factory::CameraFactory::createCamera(
    const RayTracer::Parser::CameraConfig &config)
{
    auto camera = std::make_shared<RayTracer::Camera>();
    auto [width, height] = config.getResolution();
    auto [posX, posY, posZ] = config.getPosition();
    auto [rotX, rotY, rotZ] = config.getRotation();
    double fov = config.getFov();

    camera->resolution = std::make_tuple(width, height);
    camera->fov = fov;
    camera->setPosition(posX, posY, posZ);
    camera->setRotation(rotX, rotY, rotZ);
#ifdef _DEBUG
    std::cout << "Camera created with position (" << posX << ", " << posY << ", " << posZ 
              << "), rotation (" << rotX << ", " << rotY << ", " << rotZ 
              << "), resolution " << width << "x" << height 
              << ", FOV " << fov << std::endl;
#endif

    return camera;
}
