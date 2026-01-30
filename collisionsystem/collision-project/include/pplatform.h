#ifndef PPLATFORM_H
#define PPLATFORM_H

#include "pcontacts.h"

/**
 * Platforms are two dimensional: lines on which the
 * particles can rest. Platforms are also contact generators for the physics.
 */

class Platform : public ParticleContactGenerator
{
public:
    Vector2 start;
    Vector2 end;

    const int PARTICLE_COUNT; // or whatever you use

    /**
     * Holds a pointer to the particles we're checking for collisions with.
     */
    Particle** particles; // btw, this is a pointer, to a Particle pointer

    Platform(int particle_count) : PARTICLE_COUNT(particle_count), particles(new Particle* [particle_count]) {}

    ~Platform() { delete[] particles; }


    virtual unsigned addContact(ParticleContact* contact, unsigned limit) const override;
};

#endif // PPLATFORM_H