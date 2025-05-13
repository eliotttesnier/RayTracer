/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AntialiasingConfig
*/

#include <string>

#include "AntialiasingConfig.hpp"

namespace RayTracer::Parser
{

AntialiasingConfig::AntialiasingConfig(
    const std::string &type,
    const int samples,
    const double threshold
) : _type(type), _samples(samples), _threshold(threshold)
{
}

int AntialiasingConfig::getSamples() const
{
    return _samples;
}

std::string AntialiasingConfig::getType() const
{
    return _type;
}

double AntialiasingConfig::getThreshold() const
{
    return _threshold;
}

}
