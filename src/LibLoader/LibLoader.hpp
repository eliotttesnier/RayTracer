/**
 * @file LibLoader.hpp
 * @brief Header file for the LibLoader class, responsible for dynamically loading modules.
 * 
 * This file defines the LibLoader class, which provides functionality to load and manage
 * dynamic libraries (modules) at runtime. It includes methods to retrieve module information
 * such as type, path, and name, as well as to create display module objects.
 * 
 * @author Roussiere Noa
 * @date 2023
 */

#ifndef LIBLOADER_HPP
#define LIBLOADER_HPP

#include <memory>
#include <dlfcn.h>
#include "Exception.hpp"

namespace RayTracer::Loader
{
	class LibLoader {
	protected:
		void *_moduleHandle = nullptr;
		std::string _modulePath;

	public:

		const char *getModulePath() const {return this->_modulePath.c_str();};

		template<class T, typename... Args>
		T* initEntryPointPtr(const char* entryPoint, Args&&... args) const {
			auto create = reinterpret_cast<T* (*)(Args...)>(dlsym(this->_moduleHandle, entryPoint));
			if (!create) {
				throw DLLException(std::string("Error cannot load entry point: ") + entryPoint);
			}
			return create(std::forward<Args>(args)...);
		}

		template<class T, typename... Args>
		T initEntryPoint(const char* entryPoint, Args&&... args) const {
			auto create = reinterpret_cast<T (*)(Args...)>(dlsym(this->_moduleHandle, entryPoint));
			if (!create) {
				throw DLLException(std::string("Error cannot load entry point: ") + entryPoint);
			}
			return create(std::forward<Args>(args)...);
		}

		void closeLib();

		void openLib(const std::string &path);

		LibLoader() = default;

		~LibLoader();
	};
}
#endif //LIBLOADER_HPP
