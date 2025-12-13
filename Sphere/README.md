# 2D Rigid Body Collision Detection and Response (C++ / OpenGL)

This project implements a 2D rigid body collision detection and response system in C++, using OpenGL for real-time visualisation. It models basic physical behaviour including gravity, drag, and elastic collisions within a confined window.


---

## Features

- **2D rigid bodies:** Configurable position, mass, velocity, acceleration, and geometry.
- **Collision detection:** Intersection tests between moving objects.
- **Collision response:** Physically based resolution using laws of motion.
- **Forces:** Gravity and drag integrated into the simulation loop.
- **Boundary handling:** Objects constrained within the window bounds.
- **Object-oriented design:** Polymorphism, inheritance, and clear class hierarchies.
- **Visualisation:** Real-time rendering with OpenGL.
- **Design diagrams:** UML diagrams (StarUML) for architecture and algorithm logic.

---

## Technologies

- **Language:** C++
- **Graphics:** OpenGL
- **Design:** StarUML (UML class and sequence diagrams)
- **Paradigm:** Object-oriented programming with polymorphism and inheritance

---

## Core concepts

- **Rigid body model:** Each object has:
  - Initial position and velocity
  - Mass and acceleration
  - Geometric shape for collision checks
- **Simulation loop:**
  1. Apply forces (gravity, drag)
  2. Integrate motion
  3. Detect collisions (object–object and object–bounds)
  4. Resolve collisions sequentially
  5. Render frame with OpenGL
 
## Getting started

> Note: Adjust paths and compiler options as needed for your environment.

1. **Clone the repository:**
   ```bash
   git clone https://github.com/kejiahp/collision-detection-algo.git
   cd collision-detection-algo
