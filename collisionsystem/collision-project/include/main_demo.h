#ifndef MAIN_DEMO_H
#define MAIN_DEMO_H

#include <gl/glut.h>
#include <stdio.h>
#include <utility>
#include <cassert>

#include "app.h"
#include "coreMath.h"
#include "pcontacts.h"
#include "pworld.h"
#include "pcollision.h"
#include "pplatform.h"


/**
 * @brief Demo application showcasing particle physics and collisions.
 *
 * MainDemo extends the base Application class and sets up a complete
 * particle simulation environment, including particle blobs, platforms,
 * collision generators, and a ParticleWorld to manage integration and
 * contact resolution. Rendering and per‑frame updates are handled through
 * overridden Application methods.
 */
class MainDemo : public Application
{
    /**
     * @brief Array of particles used in the demo.
     *
     * Typically represents the main set of simulated particle "blobs."
     * Ownership semantics depend on the implementation (allocated and
     * freed by the demo or externally).
     */
    Particle* blobs;

    /**
     * @brief Array of platform pointers used for collision boundaries.
     *
     * Each platform represents a static line segment that particles may
     * collide with or rest upon.
     */
    Platform** platforms;

    /**
     * @brief Broad‑phase collision generator for particle–particle contacts.
     *
     * Handles interval sorting and overlap detection to produce collision
     * contacts for the physics engine.
     */
    ParticleCollision* particleCollision;

    /**
     * @brief Physics world managing particles, forces, and contact resolution.
     */
    ParticleWorld world;

public:
    /**
     * @brief Constructs a new MainDemo instance.
     *
     * Initializes the particle system, platforms, collision structures,
     * and any other resources required for the simulation.
     */
    MainDemo();

    /**
     * @brief Destroys the demo and releases allocated resources.
     */
    virtual ~MainDemo();

    /**
     * @brief Retrieves the window title for this demo.
     *
     * @return A null‑terminated string containing the demo title.
     */
    virtual const char* getTitle();

    /**
     * @brief Renders the particle system and environment.
     *
     * Called once per frame after update(). Responsible for drawing
     * particles, platforms, and any debug visualization.
     */
    virtual void display();

    /**
     * @brief Updates the simulation state.
     *
     * Advances particle positions, resolves collisions, and updates
     * the physics world for the current frame.
     */
    virtual void update();
};


#endif // MAIN_DEMO_H