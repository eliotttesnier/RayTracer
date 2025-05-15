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
    const bool multithreading,
    const unsigned int maxThreads
) : _type(type), _multithreading(multithreading), _maxThreads(maxThreads)
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

unsigned int RenderingConfig::getMaxThreads() const
{
    return _maxThreads;
}

}
