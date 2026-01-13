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
#include <utility>
#include <iostream>
#include <cassert>


const Vector2 Vector2::GRAVITY = Vector2(0, -9.81);
constexpr int PARTICLE_COUNT = 2;
constexpr int PLATFORM_COUNT = 7;

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
    Particle* particles[PARTICLE_COUNT];

    virtual unsigned addContact(
        ParticleContact* contact,
        unsigned limit
    ) const;
};

unsigned Platform::addContact(ParticleContact* contact,
    unsigned limit) const
{
    // restitution controls how bouncy an object feels
    const static float restitution = 0.5f; // 1.0f

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


class BlobDemo : public Application
{
    Particle* blobs;

    Platform* platforms;

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

    // Create the blob storage array
    blobs = new Particle[PARTICLE_COUNT];

    // Create the platforms array
    platforms = new Platform[PLATFORM_COUNT];

    // define each platform items start and end positions
    std::pair<Vector2, Vector2> platformPositions[PLATFORM_COUNT] = { 
        {Vector2(-50.0f, 10.0f), Vector2(50.0f, 0.0f)},
        {Vector2(0.0f, -70.0f), Vector2(100.0f, -55.0f)},
        {Vector2(-20.0f, -70.0f), Vector2(-70.0f, -55.0f)},
        {Vector2(-90.0f, 90.0f), Vector2(90.0f, 90.0f)},
        {Vector2(-90.0f, 90.0f), Vector2(-90.0f, -90.0f)},
        {Vector2(-90.0f, -90.0f), Vector2(90.0f, -90.00f)},
        {Vector2(90.0f, -90.f), Vector2(90.0f, 90.0f)},
        };

    for (int i = 0; i < PLATFORM_COUNT; ++i) {
        platforms[i].start = platformPositions[i].first;
        platforms[i].end = platformPositions[i].second;
    };

    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        //if (i == 0) blobs[i].setPosition(0.0, 90.0);
        //else blobs[i].setPosition(30.0, 90.0);

        // Create the blob
        blobs[i].setRadius(5);
        blobs[i].setRandomPosition(blobs[i].getRadius(), 80.0f, 80.0f);
        blobs[i].setRandomColor();
        blobs[i].setRandomVelocity(50.0f);
        //blobs[i].setVelocity(0, 0);
        blobs[i].setDamping(1.0);
        blobs[i].setAcceleration(Vector2::GRAVITY * 20.0f);
        blobs[i].setMass(30.0f);
        blobs[i].clearAccumulator();

        // Add blob to the world particles
        world.getParticles().push_back(&blobs[i]);
    }

    // Make sure the platform knows which particle it should collide with.
    for (int i = 0; i < PLATFORM_COUNT; ++i) {
        for (int j = 0; j < PARTICLE_COUNT; ++j) {
            platforms[i].particles[j] = &blobs[j];
        }
        world.getContactGenerators().push_back(&platforms[i]);
    }

    // check for particle to platform mapping
    //for (int i = 0; i < PLATFORM_COUNT; ++i) {
    //    for(Particle * p : platforms[i].particles) {
    //        std::cout << "Platform - X: " << platforms[i].start.x << " Particle Position - X: " << p->getPosition().x << std::endl;
    //    }
    //}

    //// check for world particles
    //for (auto wp : world.getParticles()) {
    //    std::cout << "World Particle - X: " << wp->getPosition().x << std::endl;
    //}

    //// check for world contact generators/platforms
    //for(auto cg: world.getContactGenerators()) {
    //    std::cout << "Contact Generator Platform - X " << dynamic_cast<Platform*>(cg)->start.x << std::endl;
    //}
}


BlobDemo::~BlobDemo()
{
    delete[] blobs;
    delete[] platforms;
}

void BlobDemo::display()
{
    Application::display();

    // Draw Particles
    for (int i = 0; i < PLATFORM_COUNT; ++i) {
        glBegin(GL_LINES);
        glColor3f(0, 1, 1);
        glVertex2f(platforms[i].start.x, platforms[i].start.y);
        glVertex2f(platforms[i].end.x, platforms[i].end.y);
        glEnd();
    }

    // Draw Particles/Blobs
    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        glPushMatrix();
        customcolor::Color pcolor = blobs[i].getColor();
        glColor3ub(pcolor.r, pcolor.g, pcolor.b);
        glTranslatef(blobs[i].getPosition().x, blobs[i].getPosition().y, 0.0f);
        glutSolidSphere(blobs[i].getRadius(), 12, 12);
        glPopMatrix();
    }

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