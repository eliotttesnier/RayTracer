/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RenderingConfig
*/

#ifndef RENDERINGCONFIG_HPP_
#define RENDERINGCONFIG_HPP_

#include <string>

namespace RayTracer {
namespace Parser {

class RenderingConfig {
    private:
        const std::string _type;
        const bool _multithreading;

    public:
        std::string getType() const;
        bool getMultithreading() const;

        RenderingConfig() = delete;
        RenderingConfig(
            const std::string &type,
            const bool multithreading
        );
        ~RenderingConfig() = default;

    protected:
    private:
};

} // Parser
} // RayTracer

#endif /* !RENDERINGCONFIG_HPP_ */
