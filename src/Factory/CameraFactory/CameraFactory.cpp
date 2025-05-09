//
// Created by roussierenoa on 5/1/25.
//

#include "CameraFactory.hpp"
#include <iostream>
#include <memory>

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

    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);

    Math::Point3D screenOrigin(0, 0, 1);

    Math::Vector3D bottom(aspectRatio, 0, 0);
    Math::Vector3D left(0, 1, 0);
    camera->screen = RayTracer::Rectangle3D(screenOrigin, bottom, left);

    camera->transformMatrix = Math::Matrix4x4();

    camera->rotateZ(rotZ);

    camera->rotateY(-rotY);
    camera->rotateX(rotX);

    camera->setPosition(posX, posY, -posZ);

#ifdef _DEBUG
    std::cout << "Camera created with position (" << posX << ", " << posY << ", " << -posZ
              << "), rotation (" << rotX << ", " << -rotY << ", " << rotZ
              << "), resolution " << width << "x" << height
              << ", FOV " << fov
              << ", aspect ratio " << aspectRatio << std::endl;
#endif

    return camera;
}
