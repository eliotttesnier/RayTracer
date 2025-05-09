/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** MaterialFactory
*/

#ifndef MATERIALFACTORY_HPP_
#define MATERIALFACTORY_HPP_

#include <vector>
#include <memory>
#include <map>
#include <string>

#include "../../Materials/IMaterial.hpp"
#include "../../Materials/Default/DefaultMaterial.hpp"
#include "../../LibLoader/LibLoader.hpp"

namespace RayTracer::Factory {

class MaterialFactory {
    public:
        static std::shared_ptr<RayTracer::Materials::IMaterial> createMaterial(
            const std::vector<std::string> &config, 
            std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins
        );
        MaterialFactory() = default;
        ~MaterialFactory() = delete;
};

}

#endif /* !MATERIALFACTORY_HPP_ */
