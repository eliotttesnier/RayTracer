## 📝 Description

This project is a **Raytracer written in C++**, developed during our **second year at Epitech Nantes**.
It was designed to simulate the behavior of light in 3D environments using ray tracing techniques to produce **physically realistic images**.

We implemented the project in compliance with strict architecture guidelines, including **interface-based design**, use of **design patterns** (Factory, Decorator...), and optional **plugin systems** for future extensibility.

---

### 🔧 Core Features

* **Scene rendering from external config files** (libconfig++)
* **Multiple geometric primitives**: Sphere, Plane, Cylinder, Torus, OBJ file, etc.
* **Transformations**: Translation, Rotation, Scale, Shear
* **Lighting**:
  * Ambient, Directional, Point lights
  * Colored lights
  * Phong shading
  * Ambient Occlusion
* **Materials**:

  * Flat color, Reflection, Refraction, Transparency
  * Texturing (procedural & file-based)
  * Normal mapping, Chessboard, Perlin noise
* **Optimizations**: Adaptive antialiasing, Spatial partitioning, Multithreading

---

### 💻 Live Preview (Bonus)

We also developed a **live preview GUI** using **SFML**, allowing you to:

* **Navigate the scene in real-time**
* **Reload the scene on file changes**
* **Preview renders and progression before export**

---

### 📂 Scene Configuration

Scenes are described in `.cfg` files using libconfig++ syntax. You can easily define:

* Camera position, resolution, FOV
* Lighting setup
* Objects, transforms, and materials
* Scene settings (antialiasing, ambient occlusion, etc.)

**Example render:**

![Example Render](./renders/NormalMapping.png)



## 🖼️ Render Showcase

This section presents all the **rendered scenes** used to demonstrate the features implemented in the raytracer.  
Each entry includes a screenshot, a short description, and a checklist of the validated features.

### 🔗 Table of Contents
- [🖼️ NormalMapping.png](renders/NormalMapping.md)
- [🖼️ InfiniteRefraction.png](renders/InfiniteRefraction.md)
- [🖼️ ShrekOBJ.png](renders/ShrekOBJ.md)
- [🖼️ TorusReflect.png](renders/TorusReflect.md)
- [🖼️ Space.png](renders/Space.md)
- [🖼️ Transformations.png](renders/Transformations.md)
- [🖼️ MountainOfBogosses.png](renders/MountainOfBogosses.md)


## 📖 Documentation
[Notion](https://grave-algebra-657.notion.site/Technical-Documentation-Raytracer-Project-1f476f48289c8093afdffd1f9650986b?pvs=74) <br>
The documentation is available in the `doc` folder. It contains the following files:
- [doc/TechnicalDocumentation.md](doc/TechnicalDocumentation.md) : This file contains the technical documentation of the project.


## 👥 Team

This raytracer was developed as part of a **second-year project at Epitech Nantes**.

| Name   | Email                          |
|--------|--------------------------------|
| Alban  | alban.roussee@epitech.eu       |
| Eliott | eliott.tesnier@epitech.eu      |
| Nolan  | nolan.papa@epitech.eu          |
| Noa    | noa.roussiere@epitech.eu       |
