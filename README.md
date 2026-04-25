# Particle Collision & Resolution System (Sweep‑and‑Prune Physics Engine)

A real‑time 2D particle physics simulation implemented in modern C++ and OpenGL/GLUT.
The system demonstrates efficient collision detection, robust collision response, and visually rich particle behaviour using a modular physics engine architecture.

[![Demo with 1000 particles](https://github.com/kejiahp/collision-detection-algo/blob/c73de656b783289005ac347642838febc674041d/assets/s2026-02-02.png)](https://github.com/kejiahp/collision-detection-algo/blob/c73de656b783289005ac347642838febc674041d/assets/sr2026-02-02.mp4)


---

## Features
- 1000+ real‑time simulated particles (**YES, I managed to scale it to 1500+ particles😁**)

- Sweep‑and‑Prune (SAP) broad‑phase collision detection

- Circle–circle narrow‑phase collision detection

- Iterative contact solver with penetration correction

- Support for drag forces and damping

- Stable multi‑contact resolution

- OpenGL/GLUT‑based rendering

- Randomised particle:

	- Colours

	- Velocities

	- Shapes (triangle, square, pentagon, sphere)

## Technologies

- **Language:** C/C++
- **Graphics:** OpenGL
 
## Getting started

> Note: Adjust paths and compiler options as needed for your environment.

1. **Clone the repository:**
   ```bash
   git clone https://github.com/kejiahp/collision-detection-algo.git
   cd collision-detection-algo
