//
// Created on 5/13/25.
//

#ifndef ANTIALIASINGCONFIG_HPP
#define ANTIALIASINGCONFIG_HPP

#include <string>

namespace RayTracer {
namespace Parser {

class AntialiasingConfig {
    private:
        const std::string _type;
        const int _samples;
        const double _threshold;

    public:
        std::string getType() const;
        int getSamples() const;
        double getThreshold() const;

        AntialiasingConfig() = delete;
        AntialiasingConfig(
            const std::string &type,
            const int samples,
            const double threshold
        );
        ~AntialiasingConfig() = default;
};

} // Parser
} // RayTracer

#endif //ANTIALIASINGCONFIG_HPP
