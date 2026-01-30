#include <algorithm>
#include <iostream>

#include "pcollision.h"

//unsigned ParticleCollision::addContact(
//    ParticleContact* contact,
//    unsigned limit
//) const
//{
//    // BRUTE FORCE IMPLEMENTATION
//    unsigned used = 0;
//    const static float restitution = 1.0f; // 0.5f
//
//    int bruteCount = 0;
//    int maxBruteCount = 0;
//
//    for (int i = 0; i < PARTICLE_COUNT; ++i) {
//        for (int j = i + 1; j < PARTICLE_COUNT; ++j) {
//
//            if (used >= limit) return used;
//
//            Particle* A = particles[i];
//            Particle* B = particles[j];
//
//
//            Vector2 delta = A->getPosition() - B->getPosition();
//            float distance = delta.magnitude();
//
//            float totalRadius = A->getRadius() + B->getRadius();
//
//
//            if (distance <= totalRadius) {
//                contact->contactNormal = delta.unit();
//                contact->restitution = restitution;
//                contact->particle[0] = A;
//                contact->particle[1] = B;
//                contact->penetration = totalRadius - distance;
//
//                used++;
//                contact++;
//            }
//
//            ++bruteCount;
//            maxBruteCount = (((maxBruteCount) > (bruteCount)) ? (maxBruteCount) : (bruteCount));
//        }
//    }
//
//    std::cout << "MAX BRUTE COUNT: " << maxBruteCount << std::endl;
//    return used;
//}


unsigned ParticleCollision::addContact(ParticleContact* contact, unsigned limit) const
{
    //SWEEP (SORT) AND PRUNE IMPLEMENTATION
    if (limit == 0) return 0;

    // Build or update intervals
    if (firstFrame) {
        intervals.clear();
        intervals.reserve(PARTICLE_COUNT);

        for (int i = 0; i < PARTICLE_COUNT; ++i) {
            Particle* p = particles[i];
            float r = p->getRadius();
            Vector2 pos = p->getPosition();

            Interval iv;
            iv.minX = pos.x - r;
            iv.maxX = pos.x + r;
            iv.minY = pos.y - r;
            iv.maxY = pos.y + r;
            iv.p = p;

            intervals.push_back(iv);
        }

        // Initial full sort on X (O(n log n))
        std::sort(intervals.begin(), intervals.end(),
            [](const Interval& a, const Interval& b) {
                return a.minX < b.minX;
            });

        firstFrame = false;
    }
    else {
        // Update existing intervals in place
        for (auto& iv : intervals) {
            Particle* p = iv.p;
            float r = p->getRadius();
            Vector2 pos = p->getPosition();

            iv.minX = pos.x - r;
            iv.maxX = pos.x + r;
            iv.minY = pos.y - r;
            iv.maxY = pos.y + r;
        }

        // Insertion sort on nearly-sorted X (O(n))
        for (int i = 1; i < static_cast<int>(intervals.size()); ++i) {
            Interval key = intervals[i];
            int j = i - 1;

            while (j >= 0 && intervals[j].minX > key.minX) {
                intervals[j + 1] = intervals[j];
                --j;
            }
            intervals[j + 1] = key;
        }
    }

    unsigned used = 0;
    float restitution = 1.0f;
    int sapCount = 0;
    int maxSapCount = 0;
    std::vector<Interval*> active;
    active.reserve(intervals.size());

    // Sweep on X, prune on X and Y
    for (auto& current : intervals) {

        // Remove intervals that no longer overlap on X
        active.erase(
            std::remove_if(active.begin(), active.end(),
                [&](Interval* other) {
                    return other->maxX < current.minX;
                }),
            active.end()
        );

        // Check current against active set
        for (Interval* other : active) {
            if (used >= limit) return used;

            // 2-axis prune: must overlap on Y as well
            if (other->maxY < current.minY || other->minY > current.maxY) {
                continue;
            }

            Particle* A = current.p;
            Particle* B = other->p;

            // Narrow-phase: circle-circle collision

            Vector2 delta = A->getPosition() - B->getPosition();
            float distance = delta.magnitude();
            float totalRadius = A->getRadius() + B->getRadius();


            if (distance <= totalRadius) {
                contact->contactNormal = delta.unit();
                contact->restitution = restitution;
                contact->particle[0] = A;
                contact->particle[1] = B;
                contact->penetration = totalRadius - distance;

                ++sapCount;
                maxSapCount = (((maxSapCount) > (sapCount)) ? (maxSapCount) : (sapCount));

                used++;
                contact++;
            }
        }

        active.push_back(&current);
    }

    //std::cout << "MAX SAP COUNT: " << maxSapCount << std::endl;
    return used;
}