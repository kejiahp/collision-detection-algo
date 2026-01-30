#include "pplatform.h"


unsigned Platform::addContact(ParticleContact* contact, unsigned limit) const
{
    // restitution controls how bouncy an object feels, restitution of 1 (perfectly bouncy).
    const static float restitution = 1.0f; // 0.5f

    // this helps travers the contact resolver array
    unsigned int used = 0;

    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        Particle* particle = particles[i];

        // Check for penetration
        Vector2 toParticle = particle->getPosition() - start;
        Vector2 lineDirection = end - start;

        float projected = toParticle * lineDirection;
        float platformSqLength = lineDirection.squareMagnitude();
        float squareRadius = particle->getRadius() * particle->getRadius();;

        if (projected <= 0)
        {

            // The blob is nearest to the start point
            if (toParticle.squareMagnitude() < squareRadius)
            {
                // We have a collision
                contact->contactNormal = toParticle.unit();
                contact->restitution = restitution;
                contact->particle[0] = particle;
                contact->particle[1] = 0;
                contact->penetration = particle->getRadius() - toParticle.magnitude();
                used++;
                contact++;
            }

        }
        else if (projected >= platformSqLength)
        {
            // The blob is nearest to the end point
            toParticle = particle->getPosition() - end;
            if (toParticle.squareMagnitude() < squareRadius)
            {
                // We have a collision
                contact->contactNormal = toParticle.unit();
                contact->restitution = restitution;
                contact->particle[0] = particle;
                contact->particle[1] = 0;
                contact->penetration = particle->getRadius() - toParticle.magnitude();
                used++;
                contact++;
            }
        }
        else
        {
            // the blob is nearest to the middle.
            float distanceToPlatform = toParticle.squareMagnitude() - projected * projected / platformSqLength;
            if (distanceToPlatform < squareRadius)
            {
                // We have a collision
                Vector2 closestPoint = start + lineDirection * (projected / platformSqLength);

                contact->contactNormal = (particle->getPosition() - closestPoint).unit();
                contact->restitution = restitution;
                contact->particle[0] = particle;
                contact->particle[1] = 0;
                contact->penetration = particle->getRadius() - sqrt(distanceToPlatform);
                used++;
                contact++;
            }
        }
    }

    return used;
}