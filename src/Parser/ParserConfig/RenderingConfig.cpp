/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RenderingConfig
*/

#include <string>

#include "RenderingConfig.hpp"

namespace RayTracer::Parser
{

RenderingConfig::RenderingConfig(
    const std::string &type,
    const bool multithreading
) : _type(type), _multithreading(multithreading)
{
}

std::string RenderingConfig::getType() const
{
    return _type;
}

bool RenderingConfig::getMultithreading() const
{
    return _multithreading;
}

}
