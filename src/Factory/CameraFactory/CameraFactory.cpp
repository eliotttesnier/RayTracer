//
// Created by roussierenoa on 5/1/25.
//

#include "CameraFactory.hpp"

std::unique_ptr<RayTracer::Camera> raytracer::Factory::CameraFactory::createCamera(
    const raytracer::Parser::CameraConfig &config)
{
    auto [x, y, z] = config.getPosition();
    auto [rx, ry, rz] = config.getRotation();
    Math::Point3D pos(x, y, z);
    auto cam = std::unique_ptr<RayTracer::Camera>();

    cam->origin = pos;
    cam->resolution = config.getResolution();
    cam->rotateX(rx);
    cam->rotateY(ry);
    cam->rotateZ(rz);
    return cam;
}
