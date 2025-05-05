#ifndef ALIGHT_HPP
#define ALIGHT_HPP

#include "ILight.hpp"
#include "../Math/Point3D.hpp"
#include "../Math/Vector3D.hpp"

class ALight : public ILight {
    protected:
        float _x = 0.0f, _y = 0.0f, _z = 0.0f;
        float _r = 1.0f, _g = 1.0f, _b = 1.0f;
        float _intensity = 1.0f;

    public:
        ~ALight() = default;

        void setPosition(float x, float y, float z) override;
        void setColor(float r, float g, float b) override;
        void setIntensity(float intensity) override;
        virtual void setDirection(const Math::Vector3D &direction) override;

        void getPosition(float &x, float &y, float &z) const override;
        void getColor(float &r, float &g, float &b) const override;
        void getIntensity(float &intensity) const override;
        
        std::string getType() override { return "Light"; }
};

#endif // ALIGHT_HPP
