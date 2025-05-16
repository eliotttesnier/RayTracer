//
// Created by roussierenoa on 3/17/25.
//

#include "LibLoader.hpp"

#include <dlfcn.h>

#include <iostream>
#include <stdexcept>
#include <string>

namespace RayTracer::Loader {

void LibLoader::openLib(const std::string &path)
{
    this->_modulePath = path;
    #ifdef _DEBUG
        std::cout << "Opening library: " << path << std::endl;
    #endif
    try {
        this->_moduleHandle = dlopen(path.c_str(), RTLD_LAZY);
        if (!this->_moduleHandle)
            throw std::exception();
    } catch (...) {
        throw DLLException("Error during dlopen("+path+", ...): " + std::string(dlerror()));
    }
}

void LibLoader::closeLib()
{
    if (this->_moduleHandle) {
        #ifdef _DEBUG
                std::cout << "Closing library: " << this->_modulePath << std::endl;
        #endif
        dlclose(this->_moduleHandle);
        this->_moduleHandle = nullptr;
    } else {
        #ifdef _DEBUG
                std::cout << "No library to close." << std::endl;
        #endif
    }
    this->_moduleHandle = nullptr;
}

LibLoader::~LibLoader()
{
    this->closeLib();
}

}  // namespace RayTracer::Loader
