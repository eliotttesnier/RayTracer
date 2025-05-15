#ifndef RAYTRACER_CUDA_STRUCTURES_H
#define RAYTRACER_CUDA_STRUCTURES_H

#include <vector_types.h>

namespace RayTracer {
namespace CUDA {

// Structures simples pour le GPU
struct Point3D {
    float x, y, z;
};

struct Vector3D {
    float x, y, z;
};

struct Ray {
    Point3D origin;
    Vector3D direction;
};

struct Color {
    float r, g, b, a;
};

struct HitData {
    bool hit;
    float distance;
    Point3D point;
    Vector3D normal;
    Color color;
};

// Structures pour les primitives
struct Sphere {
    Point3D center;
    float radius;
    Color color;
    // Propriétés matérielles simplifiées
    float reflection;
    float refraction;
    float transparency;
};

struct Triangle {
    Point3D p1, p2, p3;
    Vector3D normal;
    Color color;
    float reflection;
    float refraction;
    float transparency;
};

struct Light {
    Point3D position;
    Vector3D direction; // Pour les lumières directionnelles
    Color color;
    float intensity;
    int type; // 0: ambient, 1: directional, 2: point
};

// Structure pour la caméra
struct Camera {
    Point3D position;
    Vector3D direction;
    Vector3D up;
    Vector3D right;
    float fov;
    float aspectRatio;
};

// Structure pour les paramètres de rendu
struct RenderParams {
    int width;
    int height;
    int maxDepth;
    int samples;
    bool useAntialiasing;
};

} // namespace CUDA
} // namespace RayTracer

#endif // RAYTRACER_CUDA_STRUCTURES_H
