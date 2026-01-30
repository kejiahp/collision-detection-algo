#ifndef PARTICLE_H
#define PARTICLE_H

#include "coreMath.h"
#include "custom_color.hpp"

/**
* @brief Represents a basic physics particle with position, velocity,
*        acceleration, mass, radius, and color.
*
* A Particle stores its physical state and supports force accumulation,
* integration, randomization utilities, and helper functions for computing
* forces such as drag and gravity. It is designed for use in a simple
* particle physics engine with Euler integration.
*/
class Particle
{
protected:
    /**
     * @brief Current position of the particle in 2D space.
     */
    Vector2 position;

    /**
     * @brief Current velocity of the particle.
     */
    Vector2 velocity;

    /**
     * @brief Current acceleration applied to the particle.
     *
     * This includes both constant acceleration (e.g., gravity) and
     * acceleration resulting from applied forces.
     */
    Vector2 acceleration;

    /**
     * @brief Accumulated forces acting on the particle for the current frame.
     *
     * This accumulator is cleared after each integration step.
     */
    Vector2 forceAccum;

    /**
     * @brief Damping factor used for simple drag simulation.
     *
     * Not recommended for use—prefer getDragForce() and add the returned
     * force to the accumulator each frame.
     */
    float damping = 0.0f;

    /**
     * @brief Radius of the particle, used for rendering and collision.
     */
    float radius = 0.0f;

    /**
     * @brief Inverse of the particle's mass.
     *
     * A value of 0 represents infinite mass (immovable object).
     */
    float inverseMass = 0.0f;

    /**
     * @brief Color assigned to the particle.
     */
    customcolor::Color color;

public:
    // --- Position ---

    /**
     * @brief Sets the particle's position.
     *
     * @param x X‑coordinate.
     * @param y Y‑coordinate.
     */
    void setPosition(const float x, const float y);

    /**
     * @brief Sets the particle's position.
     *
     * @param position New position vector.
     */
    void setPosition(const Vector2& position);

    /**
     * @brief Sets the particle's radius.
     *
     * @param r New radius value.
     */
    void setRadius(const float r);

    /**
     * @brief Retrieves the particle's current position.
     *
     * @return Position vector.
     */
    Vector2 getPosition() const;

    /**
     * @brief Retrieves the particle's radius.
     *
     * @return Radius value.
     */
    float getRadius() const;

    /**
     * @brief Integrates the particle forward in time.
     *
     * Applies accumulated forces, updates velocity and position using
     * Euler integration, and clears the force accumulator.
     *
     * @param duration Time step for integration.
     */
    void integrate(float duration);

    // --- Velocity ---

    /**
     * @brief Sets the particle's velocity.
     *
     * @param velocity New velocity vector.
     */
    void setVelocity(const Vector2& velocity);

    /**
     * @brief Sets the particle's velocity.
     *
     * @param x X‑component.
     * @param y Y‑component.
     */
    void setVelocity(const float x, const float y);

    /**
     * @brief Retrieves the particle's current velocity.
     *
     * @return Velocity vector.
     */
    Vector2 getVelocity() const;

    // --- Acceleration ---

    /**
     * @brief Sets the particle's acceleration.
     *
     * @param newAcceleration New acceleration vector.
     */
    void setAcceleration(const Vector2& newAcceleration);

    /**
     * @brief Sets the particle's acceleration.
     *
     * @param x X‑component.
     * @param y Y‑component.
     */
    void setAcceleration(const float x, const float y);

    /**
     * @brief Retrieves the particle's current acceleration.
     *
     * @return Acceleration vector.
     */
    Vector2 getAcceleration() const;

    // --- Force Accumulation ---

    /**
     * @brief Clears the D'Alembert force accumulator.
     *
     * Should be called once per frame after integration.
     */
    void clearAccumulator();

    /**
     * @brief Adds a force to the D'Alembert accumulator.
     *
     * @param force Force vector to add.
     */
    void addForce(const Vector2& force);

    // --- Forces ---

    /**
     * @brief Computes the drag force acting on the particle.
     *
     * Drag is calculated using:
     * \f[
     *     F_{drag} = -k_1 |v| - k_2 |v|^2
     * \f]
     *
     * @return The drag force vector.
     */
    Vector2 getDragForce();

    /**
     * @brief Sets the damping factor (legacy drag model).
     *
     * Not recommended—prefer getDragForce().
     *
     * @param damping Value in the range [0, 1]. Lower values produce stronger damping.
     */
    void setDamping(const float damping);

    /**
     * @brief Retrieves the damping factor.
     *
     * @return Damping value.
     */
    float getDamping() const;

    // --- Mass ---

    /**
     * @brief Sets the particle's mass.
     *
     * @param mass New mass value.
     */
    void setMass(const float mass);

    /**
     * @brief Retrieves the particle's mass.
     *
     * @return Mass value.
     */
    float getMass() const;

    /**
     * @brief Sets the inverse mass directly.
     *
     * @param inverseMass New inverse mass value.
     */
    void setInverseMass(const float inverseMass);

    /**
     * @brief Retrieves the inverse mass.
     *
     * @return Inverse mass value.
     */
    float getInverseMass() const;

    /**
     * @brief Checks whether the particle has finite (non‑infinite) mass.
     *
     * @return True if inverse mass > 0.
     */
    bool hasFiniteMass() const;

    /**
     * @brief Computes the gravitational force acting on the particle.
     *
     * @return Gravity force vector.
     */
    Vector2 getGravityForce() const;

    // --- Color ---

    /**
     * @brief Sets the particle's color.
     *
     * @param color New color value.
     */
    void setColor(const customcolor::Color& color);

    /**
     * @brief Assigns a random color to the particle.
     */
    void setRandomColor();

    /**
     * @brief Retrieves the particle's assigned color.
     *
     * @return Color value.
     */
    customcolor::Color getColor() const;

    // --- Randomization Utilities ---

    /**
     * @brief Assigns a random radius to the particle.
     *
     * Ensures the radius is less than one‑quarter of the smallest boundary.
     *
     * @param boundW Viewport width.
     * @param boundH Viewport height.
     * @param makeSmall If true, forces a smaller radius range.
     */
    void setRandomRadius(int boundW, int boundH, bool makeSmall = false);

    /**
     * @brief Assigns a random position within the window bounds.
     *
     * @param radius Particle radius (used to avoid clipping).
     * @param boundW Viewport width.
     * @param boundH Viewport height.
     */
    void setRandomPosition(float radius, float boundW, float boundH);

    /**
     * @brief Assigns a random velocity to the particle.
     *
     * @param maxVelocity Maximum absolute velocity magnitude.
     */
    void setRandomVelocity(float maxVelocity);

    /**
     * @brief Computes a physically consistent mass based on radius.
     *
     * Useful when radius and mass would otherwise produce unrealistic drag.
     *
     * @param radius Particle radius.
     * @param refRadius Reference radius for scaling (default: 5).
     * @param refMass Reference mass for scaling (default: 1).
     * @return Computed mass value.
     */
    float computeMassFromRadius(float radius, float refRadius = 5, float refMass = 1);

    /**
     * @brief Returns a string representation of the particle.
     *
     * Useful for debugging.
     *
     * @return Human‑readable string describing the particle.
     */
    std::string toString() const;
};


#endif // PARTICLE_H