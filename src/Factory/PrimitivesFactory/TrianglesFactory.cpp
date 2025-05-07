/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-eliott.tesnier
** File description:
** TrianglesFactory
*/

#include "TrianglesFactory.hpp"
#include "Primitives/Triangles/Triangles.hpp"

RayTracer::Factory::TrianglesFactory::TrianglesFactory(const Math::Point3D &p1, const Math::Point3D &p2, const Math::Point3D &p3, const Math::Vector3D &rotation, const Math::Vector3D &scale
):
    _p1(p1),
    _p2(p2),
    _p3(p3),
    _rotation(rotation),
    _scale(scale)
{

}

std::shared_ptr<IPrimitive> RayTracer::Factory::TrianglesFactory::create(std::map<std::string, std::unique_ptr<Loader::LibLoader>> &plugins) const
{
    if (!plugins.contains("Triangles"))
        throw std::runtime_error("Triangles plugin not found");
    auto obj = plugins["Triangles"]->initEntryPointPtr<primitive::Triangles>("create", this->_p1, this->_p2, this->_p3);
    obj->setRotation(this->_rotation);
    obj->setScale(this->_scale);
    return std::shared_ptr<IPrimitive>(obj, [](IPrimitive* ptr) { delete ptr; });
}
