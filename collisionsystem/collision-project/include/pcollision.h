#ifndef PARTICLE_COLLISION_H
#define PARTICLE_COLLISION_H

#include<vector>
#include "pcontacts.h"

class ParticleCollision : public ParticleContactGenerator {
public:
    /**
    * @brief Track first frame, for O(nlogn) sorting of intervals, using the default sorting algorithm
    * 
    * Subsequent sorting will be O(n) using insertion sort
    */
    mutable bool firstFrame = true;

    const int PARTICLE_COUNT; // or whatever you use

    Particle** particles; // btw, this is a pointer, to a Particle pointer

    ParticleCollision(int particle_count): PARTICLE_COUNT(particle_count), particles(new Particle*[particle_count]) {}

    ~ParticleCollision() { delete[] particles; }

    struct Interval {
        float minX, maxX;
        float minY, maxY;
        Particle* p;
    };
    mutable std::vector<Interval> intervals;


    virtual unsigned addContact(ParticleContact* contact, unsigned limit) const override;
};

#endif // PARTICLE_COLLISION_H