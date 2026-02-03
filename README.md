# Particle Collision & Resolution System (Sweep‑and‑Prune Physics Engine)

A real‑time 2D particle physics simulation implemented in modern C++ and OpenGL/GLUT.
The system demonstrates efficient collision detection, robust collision response, and visually rich particle behaviour using a modular physics engine architecture.

[![Demo with 1000 particles](https://github.com/kejiahp/collision-detection-algo/blob/c73de656b783289005ac347642838febc674041d/assets/s2026-02-02.png)](https://github.com/kejiahp/collision-detection-algo/blob/c73de656b783289005ac347642838febc674041d/assets/sr2026-02-02.mp4)


---

## Features

### Physics & Simulation
- 500+ real‑time simulated particles

- Sweep‑and‑Prune (SAP) broad‑phase collision detection

- Circle–circle narrow‑phase collision detection

- Line‑segment platform collision detection

- Impulse‑based collision response

- Iterative contact solver with penetration correction

- Support for drag forces and damping

- Stable multi‑contact resolution


### Rendering & Visualisation
- OpenGL/GLUT‑based rendering

- Randomised particle:

	- Colours

	- Velocities

	- Shapes (triangle, square, pentagon, sphere)

- Visual debugging of platforms and particle interactions



---

## Technologies

- **Language:** C++
- **Graphics:** OpenGL

---

## Core concepts

### Sweep‑and‑Prune Broad‑Phase

Efficiently reduces collision checks from $$O(n^2)$$ to near‑linear time by:

- Sorting bounding intervals along the X‑axis

- Maintaining an active list of overlapping intervals

- Pruning non‑overlapping pairs early

- Using insertion sort for temporal coherence


### Impulse‑Based Collision Response

Implements classical physics:

- Separating velocity calculation

- Restitution‑based rebound

- Impulse distribution proportional to inverse mass

- Positional correction to prevent sinking or jitter

### Iterative Contact Resolution

Resolves multiple simultaneous collisions by:

- Selecting the contact with the largest closing velocity

- Resolving velocity and penetration

- Propagating corrections across all contacts

### Modular Contact Generators
Two collision generators feed the physics world:

- `Platform` => particle vs. static line segment

- `ParticleCollision` => particle vs. particle (SAP)

 
## Getting started

> Note: Adjust paths and compiler options as needed for your environment.

1. **Clone the repository:**
   ```bash
   git clone https://github.com/kejiahp/collision-detection-algo.git
   cd collision-detection-algo
