//
// Created by roussierenoa on 5/1/25.
//

#include "CameraFactory.hpp"

#include <iostream>
#include <memory>

std::shared_ptr<RayTracer::Camera> RayTracer::Factory::CameraFactory::createCamera(
    const RayTracer::Parser::CameraConfig &config)
{
    auto [x, y, z] = config.getPosition();
    auto [rx, ry, rz] = config.getRotation();
    Math::Point3D pos(x, y, z);
    auto cam = std::make_shared<RayTracer::Camera>();

    cam->origin = pos;
    cam->resolution = config.getResolution();
    cam->fov = config.getFov();
    cam->rotateX(rx);
    cam->rotateY(ry);
    cam->rotateZ(rz);
#ifdef _DEBUG
    std::cout << "Creating a camera" << std::endl;
#endif
    return cam;
}
