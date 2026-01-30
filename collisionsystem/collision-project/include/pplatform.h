#ifndef PPLATFORM_H
#define PPLATFORM_H

#include "pcontacts.h"

/**
 * @brief Represents a 2D platform used for particle collision detection.
 *
 * A Platform is defined by a line segment in 2D space. Particles may rest on
 * or collide with this platform, and the class acts as a contact generator
 * for the physics system. Each platform checks a set of particles and
 * produces collision contacts when intersections occur.
 */
class Platform : public ParticleContactGenerator
{
public:
    /**
     * @brief Starting point of the platform line segment.
     */
    Vector2 start;

    /**
     * @brief Ending point of the platform line segment.
     */
    Vector2 end;

    /**
     * @brief Number of particles monitored for collisions.
     *
     * This value is fixed at construction time and determines the size
     * of the internal particle pointer array.
     */
    const int PARTICLE_COUNT;

    /**
     * @brief Array of pointers to particles being tested against this platform.
     *
     * Each entry is a pointer to a Particle object. The Platform does not
     * own the Particle instances themselves—only the array of pointers.
     */
    Particle** particles;

    /**
     * @brief Constructs a Platform and allocates storage for particle pointers.
     *
     * @param particle_count Number of particles that will be checked for
     *        collisions with this platform.
     */
    Platform(int particle_count)
        : PARTICLE_COUNT(particle_count),
        particles(new Particle* [particle_count])
    {
    }

    /**
     * @brief Destructor that releases the particle pointer array.
     *
     * Note that this does not delete the Particle objects themselves,
     * only the array that stores their pointers.
     */
    ~Platform()
    {
        delete[] particles;
    }

    /**
     * @brief Generates collision contacts between the platform and its particles.
     *
     * This method checks each particle against the platform line segment.
     * If a collision or resting contact is detected, a new ParticleContact
     * is written into the provided contact array (up to @p limit entries).
     *
     * @param contact Pointer to the first available contact in the contact array.
     * @param limit Maximum number of contacts that may be written.
     * @return The number of contacts actually generated.
     */
    virtual unsigned addContact(ParticleContact* contact,
        unsigned limit) const override;
};


#endif // PPLATFORM_H