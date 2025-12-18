/*
 * The Blob demo.
 *
 */
#include <gl/glut.h>
#include "app.h"
#include "coreMath.h"
#include "pcontacts.h"
#include "pworld.h"
#include <stdio.h>
#include <cassert>


const Vector2 Vector2::GRAVITY = Vector2(0, -9.81);

/**
 * Platforms are two dimensional: lines on which the
 * particles can rest. Platforms are also contact generators for the physics.
 */

class Platform : public ParticleContactGenerator
{
public:
    Vector2 start;
    Vector2 end;
    /**
     * Holds a pointer to the particles we're checking for collisions with.
     */
    Particle* particles[2];

    virtual unsigned addContact(
        ParticleContact* contact,
        unsigned limit
    ) const;
};

unsigned Platform::addContact(ParticleContact* contact,
    unsigned limit) const
{
    const static float restitution = 0.5f;
    //const static float restitution = 1.0f;
    unsigned used;

    for (Particle *particle : particles) {
        used = 0;

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


class BlobDemo : public Application
{
    Particle* blob;
    Particle* blob2;

    Platform* platform;
    Platform* platform2;
    Platform* platform3;

    ParticleWorld world;

public:
    /** Creates a new demo object. */
    BlobDemo();
    virtual ~BlobDemo();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particles. */
    virtual void display();

    /** Update the particle positions. */
    virtual void update();

};

// Method definitions
BlobDemo::BlobDemo() :world(2, 1)
{
    width = 400; height = 400;
    nRange = 100.0;

    // Create the blob storage
    blob = new Particle;
    blob2 = new Particle;

    // Create the platform
    platform = new Platform;
    platform2 = new Platform;
    platform3 = new Platform;

    platform->start = Vector2(-50.0, 10.0);
    platform->end = Vector2(50.0, 0.0);

    platform2->start = Vector2(0.0, -70.0);
    platform2->end = Vector2(80.0, -55.0);

    platform3->start = Vector2(-20.0, -70.0);
    platform3->end = Vector2(-70.0,-55.0);

    // Make sure the platform knows which particle it should collide with.
    platform->particles[0] = blob;
    platform2->particles[0] = blob;
    platform3->particles[0] = blob;

    platform->particles[1] = blob2;
    platform2->particles[1] = blob2;
    platform3->particles[1] = blob2;

    world.getContactGenerators().push_back(platform);
    world.getContactGenerators().push_back(platform2);
    world.getContactGenerators().push_back(platform3);

    // Create the blob
    blob->setPosition(0.0, 90.0);
    blob->setRadius(5);
    blob->setVelocity(0, 0);
    //blob->setDamping(0.9);
    blob->setDamping(1.0);
    blob->setAcceleration(Vector2::GRAVITY * 20.0f);

    blob->setMass(30.0f);
    blob->clearAccumulator();
    world.getParticles().push_back(blob);

    // Create the blob
    blob2->setPosition(30.0, 90.0);
    blob2->setRadius(5);
    blob2->setVelocity(0, 0);
    //blob->setDamping(0.9);
    blob2->setDamping(1.0);
    blob2->setAcceleration(Vector2::GRAVITY * 20.0f);

    blob2->setMass(30.0f);
    blob2->clearAccumulator();
    world.getParticles().push_back(blob2);
}


BlobDemo::~BlobDemo()
{
    delete blob;
    delete blob2;
}

void BlobDemo::display()
{
    Application::display();

    const Vector2& p0 = platform->start;
    const Vector2& p1 = platform->end;

    glBegin(GL_LINES);
    glColor3f(0, 1, 1);
    glVertex2f(p0.x, p0.y);
    glVertex2f(p1.x, p1.y);
    glEnd();

    // Particle 2
    glBegin(GL_LINES);
    glColor3f(0, 1, 1);
    glVertex2f(platform2->start.x, platform2->start.y);
    glVertex2f(platform2->end.x, platform2->end.y);
    glEnd();

    // Particle 3
    glBegin(GL_LINES);
    glColor3f(0, 1, 1);
    glVertex2f(platform3->start.x, platform3->start.y);
    glVertex2f(platform3->end.x, platform3->end.y);
    glEnd();

    const Vector2& p = blob->getPosition();
    glPushMatrix();
    glColor3f(0, 255, 0);
    glTranslatef(p.x, p.y, 0);
    glutSolidSphere(blob->getRadius(), 12, 12);
    glPopMatrix();

    glPushMatrix();
    glColor3f(255, 0, 0);
    glTranslatef(blob2->getPosition().x, blob2->getPosition().y, 0);
    glutSolidSphere(blob2->getRadius(), 12, 12);
    glPopMatrix();

    glutSwapBuffers();

}

void BlobDemo::update()
{
    // Recenter the axes
    float duration = timeinterval / 1000;
    // Run the simulation
    world.runPhysics(duration);

    Application::update();
}

const char* BlobDemo::getTitle()
{
    return "Blob Demo";
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
    return new BlobDemo();
}