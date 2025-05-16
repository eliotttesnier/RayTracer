# 🧠 Technical Documentation – Raytracer Project

# 📋 Table of Contents

1. [Introduction](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
2. [High-Level Architecture](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
3. [Plugin System Overview](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
    1. [Purpose](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
    2. [Primitive Interface](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        1. [Abstract Base (`APrimitive`)](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        2. [Plugin Entry Point](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        3. [Class Responsibilities](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        4. [Extending the Engine](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        5. [Example](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
    3. [Light Interface](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        1. [Abstract Base (`ALight`)](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        2. [Plugin Entry Point](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        3. [Class Responsibilities](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        4. [Extending the Engine](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)
        5. [Example](https://www.notion.so/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=21)

---

# 🧭 Introduction

This document explains the internal structure of the **Raytracer** project and how to extend it using a **plugin-based architecture**. The goal is to allow the addition of new primitives and lights without modifying or recompiling the core engine.

---

# 🧱 High-Level Architecture

The high-level architecture flow is shown below:

```
   ┌──────────┐   
   │          │   
   │  Parser  │   
   │          │   
   └────┬─────┘   
        │         
        ▼         
┌────────────────┐
│                │
│ Plugins loader │
│                │
└───────┬────────┘
        │         
        ▼         
   ┌─────────┐    
   │         │    
   │ Factory │    
   │         │    
   └────┬────┘    
        │         
        ▼         
   ┌──────────┐   
   │          │   
   │ Renderer │   
   │          │   
   └────┬─────┘   
        │         
        ▼         
┌────────────────┐
│                │
│ Graphic Render │
│                │
└────────────────┘
```

This is the Raytracer execution process

```
                                                  ┌─────────────────────┐
                                                  │                     │
                                                  │ Antialiasing Config │
                                             ┌───►│                     │
                                             │    └─────────────────────┘
                                             │    ┌───────────────┐      
                                             │    │               │      
                                             ├───►│ Camera Config │      
                                             │    │               │      
                                             │    └───────────────┘      
      ┌────────────┐      ┌──────────┐       │    ┌───────────────┐      
      │            │      │          │       │    │               │      
      │ config.cfg ├─────►│  Parser  │───────┼───►│ Lights Config │      
      │            │      │          │       │    │               │      
      └────────────┘      └──────────┘       │    └───────────────┘      
                                             │    ┌───────────────────┐  
                                             │    │                   │  
                                             │    │ Primitives Config │  
                                             ├───►│                   │  
                                             │    └───────────────────┘  
                                             │    ┌──────────────────┐   
                                             │    │                  │   
                                             └───►│ Rendering Config │   
                                                  │                  │   
                                                  └──────────────────┘   
                                                                         
                                                         ┌────────────┐  
 ┌────────────────┐       ┌────────────────────┐    ┌───►│ IPrimitive │  
 │                │ (.so) │                    │(or)│    └────────────┘  
 │ ./plugins/*.so ├──────►│   Plugins loader   ├────┤                    
 │                │       │                    │    │    ┌────────┐      
 └────────────────┘       └────────────────────┘    └───►│ ILight │      
                                                         └────────┘      
                                                                         
                                                                         
    ┌───────────────┐                                      ┌────────────┐
    │               │                      ┌─────────┐     │            │
    │ Camera Config ┼────┐                 │         │ ┌──►│ Primitives │
    │               │    │                 │         │ │   │            │
    └───────────────┘    │                 │         │ │   └────────────┘
    ┌───────────────┐    │ ┌─────────┐     │         │ │   ┌────────┐    
    │               │    │ │         │     │         │ │   │        │    
    │ Lights Config ├────┼►│ Factory ├────►│ Plugins │─┼──►│ Lights │    
    │               │    │ │         │     │         │ │   │        │    
    └───────────────┘    │ └─────────┘     │         │ │   └────────┘    
┌───────────────────┐    │                 │         │ │   ┌────────┐    
│                   │    │                 │         │ │   │        │    
│ Primitives Config ├────┘                 │         │ └──►│ Camera │    
│                   │                      └─────────┘     │        │    
└───────────────────┘                                      └────────┘    
                                                                         
                                                                         
       ┌────────────┐                                                    
       │            │                                                    
       │ Primitives ├─┐                                                  
       │            │ │                                                  
       └────────────┘ │                                                  
           ┌────────┐ │  ┌──────────┐     ┌──────────┐                   
           │        │ │  │          │     │          │                   
           │ Lights ├─┼─►│ Renderer ├────►│ file.ppm │                   
           │        │ │  │          │     │          │                   
           └────────┘ │  └──────────┘     └──────────┘                   
           ┌────────┐ │                                                  
           │        │ │                                                  
           │ Camera ├─┘                                                  
           │        │                                                    
           └────────┘                                                    
                                                                         
                                              ┌──────────┐               
                                              │          │               
      ┌──────────┐    ┌────────────────┐   ┌─►│ file.png │               
      │          │    │                ├───┘  │          │               
      │ file.ppm ├───►│ Graphic Render │      └──────────┘               
      │          │    │                ├───┐  ┌─────────┐                
      └──────────┘    └────────────────┘   │  │         │                
                                           └─►│ preview │                
                                              │         │                
                                              └─────────┘                
```

- `Parser` Load the *.cfg* file passed in input and create config class.
- `Plugins Loader` Load every compatible plugins (see bellow) from the plugins folder.
- `Factory` Convert all config class in to element thank to plugins.
- `Render` Render all scene, compute lighting… and create a .ppm file who’s a pixel file
- `Graphic Render`  Display and convert .ppm file to .png file

---

# 🔌 Plugin System Overview

## 🎯 Purpose

To allow **modular** and **extensible** support for new shapes and lights using **runtime-loaded shared libraries** (`.so`), without changing the core engine.

---

## 🧱 Primitive Interface (`IPrimitive`)

```cpp
#IPrimitive.hpp

class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        // Getters
        virtual const std::string getName() const = 0;
        virtual const Math::Point3D getPosition() const = 0;
        virtual const Math::Vector3D getRotation() const = 0;
        virtual const Math::Vector3D getShear() const = 0;
        virtual const RayTracer::primitive::AABB getBoundingBox() const = 0;

        // Setters
        virtual void setName(const std::string &name) = 0;
        virtual void setPosition(const Math::Point3D &position) = 0;
        virtual void setRotation(const Math::Vector3D &rotation) = 0;
        virtual void setScale(const Math::Vector3D &scale) = 0;
        virtual void setShear(const Math::Vector3D &shear) = 0;
        virtual void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) = 0;
        virtual void setColor(const Graphic::color_t &color) = 0;

        // Methods
        virtual Math::hitdata_t intersect(const Math::Ray &ray) = 0;
        virtual Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) = 0;
};
```

### 🧩 Abstract Base (`APrimitive`)

```cpp
#APrimitive.hpp

class APrimitive : public IPrimitive {
    protected:
        std::string _name;
        Math::Point3D _position;
        Graphic::color_t _color;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Vector3D _shear;
        Math::Vector3D _anchorPoint;
        std::shared_ptr<RayTracer::Materials::IMaterial> _material;
        AABB _boundingBox;

    public:
        virtual ~APrimitive() = default;

        // Getters
        const std::string getName() const override;
        const Math::Point3D getPosition() const override;
        const Math::Vector3D getRotation() const override;
        const Math::Vector3D getShear() const override;
        const RayTracer::primitive::AABB getBoundingBox() const override;

        // Setters
        void setName(const std::string &name) override;
        void setPosition(const Math::Point3D &position) override;
        void setRotation(const Math::Vector3D &rotation) override;
        void setScale(const Math::Vector3D &scale) override;
        void setShear(const Math::Vector3D &shear) override;
        void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) override;
        void setColor(const Graphic::color_t &color) override;

        // Methods
        Math::hitdata_t intersect(const Math::Ray &ray) override;
        Graphic::color_t getColor(
            Math::hitdata_t hitData,
            Math::Ray ray,
            std::vector<std::shared_ptr<ILight>> lights,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) override;

        Math::Ray transformRayToLocal(const Math::Ray &ray) const;
        Math::Point3D transformPointToLocal(const Math::Point3D &point) const;
        Math::Point3D transformPointToWorld(const Math::Point3D &localPoint) const;
        Math::Vector3D transformNormalToWorld(const Math::Vector3D &localNormal) const;

        void rotatePointToLocal(Math::Point3D &point, double cosX, double sinX,
                               double cosY, double sinY, double cosZ, double sinZ) const;
        void rotateVectorToLocal(Math::Vector3D &vector, double cosX, double sinX,
                                double cosY, double sinY, double cosZ, double sinZ) const;
        void rotatePointToWorld(Math::Point3D &point, double cosX, double sinX,
                               double cosY, double sinY, double cosZ, double sinZ) const;
        void rotateVectorToWorld(Math::Vector3D &vector, double cosX, double sinX,
                                double cosY, double sinY, double cosZ, double sinZ) const;
};
```

### 🚪 Plugin Entry Point

```cpp
#EntryPoint.cpp

extern "C" {
    RayTracer::primitive::MyPrimtive *create(/*Params*/)
    {
        return new RayTracer::primitive::MyPrimtive(/*Params*/);
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::PRIMITIVE_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib MyPrimtive" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib MyPrimtive" << std::endl;
#endif
    }
}
```

### 🧾 Class Responsibilities

`getName` / `setName`

Used to debug and identify primitives.

---

`getPosition` / `setPosition`

Manages the primitive's 3D location in the scene using `Math::Point3D(x, y, z)`.

---

`getRotation` / `setRotation`

Stores rotation in Euler angles as `Math::Vector3D`.

---

`getShear` / `setShear`

Defines shearing transformation (non-uniform angle deformation).

---

`setScale`

Scales the primitive along x/y/z axes.

---

`setMaterial`

Assigns a surface material using a pointer to `IMaterial`.

---

`getColor(hitData, ray, lights, primitives)`

Returns the final color at a point based on lighting and material.

---

`intersect(ray)`

Returns `hitdata_t` if the ray intersects the primitive.

---

### ➕ Extending the Engine

To add a new primitive plugin:

1. Create a new class inheriting from `APrimitive`.
2. Implement `intersect()` and `getColor()` based on shape geometry.
3. Export your class using `create()` and `getType()`.
4. Compile to a `.so` and place in the `/plugins/` directory.

---

### 📦 E**xample**

```cpp
#Sphere.hpp

Sphere::Sphere() {
    _name = "sphere";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = 1.0;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_radius, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _radius, _radius);
}

Sphere::Sphere(const Math::Point3D &position, double radius) {
    _name = "sphere";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _radius = radius;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    _boundingBox.min = Math::Point3D(-_radius, -_radius, -_radius);
    _boundingBox.max = Math::Point3D(_radius, _radius, _radius);
}

double Sphere::getRadius() const {
    return _radius;
}

void Sphere::setRadius(double radius) {
    _radius = radius;
}

Math::Vector3D Sphere::normalAt(const Math::Point3D& point) const {
    Math::Point3D localPoint = transformPointToLocal(point);
    Math::Vector3D localNormal(
        localPoint._x,
        localPoint._y,
        localPoint._z
    );
    localNormal.normalize();

    return transformNormalToWorld(localNormal);
}

Math::hitdata_t Sphere::intersect(const Math::Ray &ray) {
    Math::Ray localRay = transformRayToLocal(ray);
    Math::hitdata_t hitData;
    hitData.hit = false;

    if (!_boundingBox.intersect(localRay))
        return hitData;

    Math::Vector3D oc(localRay.origin._x, localRay.origin._y, localRay.origin._z);

    double a = localRay.direction.dot(localRay.direction);
    double b = 2.0 * oc.dot(localRay.direction);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hitData;

    double sqrtd = sqrt(discriminant);
    double t1 = (-b - sqrtd) / (2.0 * a);
    double t2 = (-b + sqrtd) / (2.0 * a);
    double t;

    if (t1 > 0.001) {
        t = t1;
        hitData.hit = true;
    } else if (t2 > 0.001) {
        t = t2;
        hitData.hit = true;
    } else {
        return hitData;
    }

    if (hitData.hit) {
        hitData.distance = t;

        Math::Point3D localHitPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        Math::Vector3D localNormal(localHitPoint._x, localHitPoint._y, localHitPoint._z);
        localNormal.normalize();

        hitData.point = transformPointToWorld(localHitPoint);
        hitData.normal = transformNormalToWorld(localNormal);
    }

    hitData.color = _color;
    return hitData;
}

Graphic::color_t Sphere::getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _material->calculateColor(
        *this,
        hitData,
        ray,
        lights,
        primitives
    );
}
```

This is a example of a Sphere primitive

---

## 💡 Light Interface (`ILight`)

```cpp
#ILight.hpp

class ILight {
    public:
        virtual ~ILight() = default;

        // Basic light properties setters
        virtual void setPosition(const Math::Point3D &pos) = 0;
        virtual void setColor(int r, int g, int b) = 0;
        virtual void setIntensity(float intensity) = 0;
        virtual void setDirection(const Math::Vector3D &direction) = 0;

        // Basic light properties getters
        virtual Math::Point3D getPosition() const = 0;
        virtual std::tuple<int, int, int> getColor() const = 0;
        virtual float getIntensity() const = 0;
        virtual std::string getLightName() const = 0;
        virtual Math::Vector3D getDirection() const = 0;
        virtual std::string getType() = 0;

        // Check if this light illuminates the hit point (visibility test)
        virtual lightInfos_t intersect(
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) const = 0;

        // Helper method to check if point is in shadow
        virtual bool isInShadow(
            const Math::Point3D& hitPoint,
            const Math::Vector3D& lightDir,
            const std::vector<std::shared_ptr<IPrimitive>>& primitives
        ) const = 0;
};
```

### 🧩 Abstract Base (`ALight`)

```cpp
#ALight.hpp

class ALight : public ILight {
    protected:
        Math::Point3D _position;
        float _r = 1.0f, _g = 1.0f, _b = 1.0f;
        float _intensity = 1.0f;
        std::string _lightName = "NONE";

    public:
        ~ALight() = default;

        // Implementation of basic setters and getters
        void setPosition(const Math::Point3D &pos) override;
        void setColor(int r, int g, int b) override;
        void setIntensity(float intensity) override;
        void setDirection(const Math::Vector3D &direction) override;

        Math::Point3D getPosition() const override;
        std::tuple<int, int, int> getColor() const override;
        float getIntensity() const override;
        std::string getLightName() const override;
        Math::Vector3D getDirection() const override;

        std::string getType() override { return "Light"; }

        // Default implementation for shadow checking
        // Derived classes can override if they have special shadow behavior
        bool isInShadow(
            const Math::Point3D& hitPoint,
            const Math::Vector3D& lightDir,
            const std::vector<std::shared_ptr<IPrimitive>>& primitives
        ) const override;

        // Each light type must implement these
        virtual lightInfos_t intersect(
            const Math::Point3D &hitPoint,
            std::vector<std::shared_ptr<IPrimitive>> primitives
        ) const = 0;
};

```

### 🚪 Plugin Entry Point

```cpp
#EntryPoint.cpp

extern "C" {
    ILight *create(/*Param*/) {
        return new RayTracer::light::MyLight(/*Param*/);
    }
    RayTracer::Loader::ModuleType getType(void) {
        return RayTracer::Loader::ModuleType::LIGHT_MODULE;
    }
    __attribute__((constructor)) void construct()
    {
#ifdef _DEBUG
        std::cout << "Loaded dynamic lib: Lib MyLight" << std::endl;
#endif
    }
    __attribute__((destructor)) void deconstruct()
    {
#ifdef _DEBUG
        std::cout << "Unloaded dynamic lib: Lib MyLight" << std::endl;
#endif
    }
}
```

### 🧾 Class Responsibilities

`getLightName`

Used to **identify and debug** light sources. Useful in logs or editor UIs.

---

`getPosition` / `setPosition`

Handles the **light’s position in the 3D scene** using `Math::Point3D(x, y, z)`.

Crucial for point lights and spotlights that originate from a specific location.

---

`getDirection` / `setDirection`

Stores the **direction vector** of the light using `Math::Vector3D(x, y, z)`.

Used by directional and spotlights to determine where the light is cast.

---

`getColor` / `setColor`

Defines the **RGB color** of the light using three integers (`r`, `g`, `b`).

Affects how the light tints illuminated objects.

---

`getIntensity` / `setIntensity`

Controls how **strong or dim** the light is.

Affects final brightness in lighting calculations.

---

`getType`

Returns the **module type** (e.g., `"Light"`).

Used internally by the loader system to categorize modules.

---

`intersect(hitPoint, primitives)`

Calculates **light contribution** at a given point.

Takes into account light properties and object occlusion.

Returns a `lightInfos_t` structure containing necessary shading data.

---

`isInShadow(hitPoint, lightDir, primitives)`

Determines whether a point is **occluded from the light** by any primitive.

Returns `true` if something blocks the light, otherwise `false`.

---

### ➕ Extending the Engine

To add a **custom light type**, implement the `ILight` interface or extend the base class `ALight` for shared behavior (e.g., color, position, intensity).

This allows the engine to dynamically load and use new lighting models (point, directional, spot, etc.) at runtime.

---

### 📦 E**xample**

```cpp
#DirectionalLight.cpp

DirectionalLight::DirectionalLight(const Math::Vector3D &direction)
    : _direction(direction)
{
    this->_lightName = "DirectionalLight";
}

void DirectionalLight::setDirection(const Math::Vector3D &direction)
{
    _direction = direction;
}

Math::Vector3D DirectionalLight::getDirection() const
{
    return _direction;
}

lightInfos_t DirectionalLight::intersect(
    const Math::Point3D &hitPoint,
    std::vector<std::shared_ptr<IPrimitive>> primitives
) const
{
    Math::Vector3D lightDir = -_direction.normalized();
    lightInfos_t infos;
    infos.hit = !isInShadow(hitPoint, lightDir, primitives);
    infos.lightDir = lightDir;
    return infos;
}
```

This is a example of a directional light