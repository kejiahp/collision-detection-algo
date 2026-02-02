#ifndef PARTICLE_COLLISION_H
#define PARTICLE_COLLISION_H

#include<vector>
#include "pcontacts.h"

/**
 * @brief Broad-phase particle–particle collision generator.
 *
 * This class performs broad-phase collision detection using interval
 * bounding boxes along both axes. It maintains a list of particles and
 * computes overlapping intervals to determine potential collision pairs.
 *
 * The first frame uses an O(n log n) sort to establish interval order.
 * Subsequent frames use insertion sort for O(n) resorting, assuming
 * temporal coherence between frames.
 */
class ParticleCollision : public ParticleContactGenerator {
private:
    /**
    * @brief Restitution controls how bouncy an object feels, restitution of 1 (perfectly bouncy). 
    */
    const float restitution;
public:

    /**
     * @brief Indicates whether this is the first update frame.
     *
     * On the first frame, interval lists are sorted using the default
     * O(n log n) sorting algorithm. Afterward, insertion sort is used
     * to maintain ordering efficiently.
     */
    mutable bool firstFrame = true;

    /**
     * @brief Number of particles monitored for collision generation.
     *
     * This value is fixed at construction and determines the size of
     * the internal particle pointer array.
     */
    const int PARTICLE_COUNT;

    /**
     * @brief Array of pointers to particles being tested for collisions.
     *
     * Each entry is a pointer to a Particle object. The ParticleCollision
     * class owns only the array of pointers—not the Particle instances.
     */
    Particle** particles;

    /**
     * @brief Constructs a ParticleCollision generator.
     *
     * Allocates an array of particle pointers of size @p particle_count.
     *
     * @param particle_count Number of particles to track for collisions.
     */
    ParticleCollision(int particle_count, float restitution)
        : PARTICLE_COUNT(particle_count),
        particles(new Particle* [particle_count]), restitution(restitution)
    {
    }

    /**
     * @brief Destructor that releases the particle pointer array.
     *
     * Note that this does not delete the Particle objects themselves,
     * only the array that stores their pointers.
     */
    ~ParticleCollision() {
        delete[] particles;
    }

    /**
     * @brief Axis-aligned bounding interval for a particle.
     *
     * Each interval stores the minimum and maximum extents of a particle
     * along both X and Y axes, along with a pointer to the particle it
     * represents. These intervals are used for broad-phase overlap tests.
     */
    struct Interval {
        float minX;  ///< Minimum X extent of the particle.
        float maxX;  ///< Maximum X extent of the particle.
        float minY;  ///< Minimum Y extent of the particle.
        float maxY;  ///< Maximum Y extent of the particle.
        Particle* p; ///< Pointer to the particle represented by this interval.
    };

    /**
     * @brief Cached list of bounding intervals for broad-phase sorting.
     *
     * This vector is mutable so it can be updated even when the collision
     * generator is referenced through a const pointer.
     */
    mutable std::vector<Interval> intervals;

    /**
     * @brief Generates collision contacts between overlapping particles.
     *
     * Performs broad-phase interval sorting and overlap checks to identify
     * potential particle–particle collisions. For each detected overlap,
     * a ParticleContact is written into the provided contact array, up to
     * the specified @p limit.
     *
     * @param contact Pointer to the first available contact in the array.
     * @param limit Maximum number of contacts that may be written.
     * @return The number of contacts actually generated.
     */
    virtual unsigned addContact(ParticleContact* contact,
        unsigned limit) const override;
};


#endif // PARTICLE_COLLISION_H