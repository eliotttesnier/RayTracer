#ifndef RAYTRACER_CONE_HPP
#define RAYTRACER_CONE_HPP

#include "../IPrimitive.hpp"

namespace RayTracer::primitive {

class Cone : public IPrimitive {
    public:
        //constructors & destructors
        Cone();
        Cone(const Math::Point3D &position, double radius = 1.0, double height = 1.0);
        ~Cone() = default;

        //getters
        std::string &getName() override;
        std::string &getType() override;
        Math::Point3D &getPosition() override;
        Math::Vector3D &getRotation() override;
        double getRadius() const;
        double getHeight() const;

        // setters
        void setRadius(double radius);
        void setHeight(double height);

        //methods
        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Math::Vector3D normalAt(const Math::Point3D& point) const;

    private:
        //attributes
        std::string _name;
        std::string _type;
        Math::Point3D _position;
        Math::Vector3D _rotation;
        double _radius;
        double _height;
};

} // namespace Raytracer::primitive

#endif //RAYTRACER_CONE_HPP
