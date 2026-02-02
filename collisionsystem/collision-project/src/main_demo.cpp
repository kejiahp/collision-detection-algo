#include "main_demo.h"

const Vector2 Vector2::GRAVITY = Vector2(0, -9.81);
constexpr int PARTICLE_COUNT = 1000;
constexpr int PLATFORM_COUNT = 7;
/**
* @breif Restitution controls how bouncy an object feels, restitution of 1 (perfectly bouncy).
*/
constexpr int RESTITUTION = 1.0f;
constexpr int INIT_WIDTH = 500;
constexpr int INIT_HEIGHT = 500;

// Method definitions
MainDemo::MainDemo() :world(PARTICLE_COUNT, 0)
{
    width = INIT_WIDTH; height = INIT_HEIGHT;
    nRange = 200.0;

    // Create the blob storage array
    blobs = new Particle[PARTICLE_COUNT];

    // Create the platforms array
    platforms = new Platform*[PLATFORM_COUNT];
    for (int i = 0; i < PLATFORM_COUNT; ++i) { platforms[i] = new Platform(PARTICLE_COUNT, RESTITUTION); }

    // Create particle-particle collision generator
    particleCollision = new ParticleCollision(PARTICLE_COUNT, RESTITUTION);


    // define each platform items start and end positions
    std::pair<Vector2, Vector2> platformPositions[PLATFORM_COUNT] = {
        {Vector2(-50.0f, 10.0f), Vector2(50.0f, 0.0f)},
        {Vector2(0.0f, -70.0f), Vector2(100.0f, -55.0f)},
        {Vector2(-20.0f, -70.0f), Vector2(-70.0f, -55.0f)},
        { Vector2(-150.0f,  100.0f), Vector2(150.0f,  100.0f) },
        { Vector2(-150.0f, -100.0f), Vector2(150.0f, -100.0f) },
        { Vector2(-150.0f,  100.0f), Vector2(-150.0f, -100.0f) },
        { Vector2(150.0f,  100.0f), Vector2(150.0f, -100.0f) }
        };

    //// rectangle200by200
    //    { Vector2(-100.0f, 100.0f), Vector2(100.0f, 100.0f) },
    //    { Vector2(-100.0f, 100.0f), Vector2(-100.0f, -100.0f) },
    //    { Vector2(-100.0f, -100.0f), Vector2(100.0f, -100.0f) },
    //    { Vector2(100.0f, -100.0f), Vector2(100.0f, 100.0f) },

    //// rectangle300by150
    //    // Top edge
    //    { Vector2(-150.0f,  75.0f), Vector2(150.0f,  75.0f) },
    //    // Bottom edge
    //    { Vector2(-150.0f, -75.0f), Vector2(150.0f, -75.0f) },
    //    // Left edge
    //    { Vector2(-150.0f,  75.0f), Vector2(-150.0f, -75.0f) },
    //    // Right edge
    //    { Vector2(150.0f,  75.0f), Vector2(150.0f, -75.0f) }



    for (int i = 0; i < PLATFORM_COUNT; ++i) {
        platforms[i]->start = platformPositions[i].first;
        platforms[i]->end = platformPositions[i].second;
    };

    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        // Create the blob
        //blobs[i].setRandomRadius(120.0f, 120.0f, true);
        blobs[i].setRadius(2);
        blobs[i].setRandomPosition(blobs[i].getRadius(), 100.0f, 100.0f);
        blobs[i].setRandomColor();
        blobs[i].setRandomVelocity(100.0f);
        //blobs[i].setVelocity(0, 0.0f);
        //blobs[i].setDamping(1.0);
        //blobs[i].setAcceleration(Vector2::GRAVITY);
        blobs[i].setMass(100.0f);
        blobs[i].clearAccumulator();

        // Add blob to the world particles
        world.getParticles().push_back(&blobs[i]);
    }

    // Give it access to all blobs
    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        particleCollision->particles[i] = &blobs[i];
    }


    // Make sure the platform knows which particle it should collide with.
    for (int i = 0; i < PLATFORM_COUNT; ++i) {
        for (int j = 0; j < PARTICLE_COUNT; ++j) {
            platforms[i]->particles[j] = &blobs[j];
        }
        world.getContactGenerators().push_back(&(*platforms[i]));
    }

    // Register with the world
    world.getContactGenerators().push_back(particleCollision);
}


MainDemo::~MainDemo()
{
    // Delete particle array
    if (blobs) {
        delete[] blobs;
        blobs = nullptr;
    }

    // Delete platforms and the array holding them
    if (platforms) {
        for (int i = 0; i < PLATFORM_COUNT; ++i) {
            delete platforms[i];   // delete each Platform*
        }
        delete[] platforms;         // delete the array of pointers
        platforms = nullptr;
    }

    // Delete collision generator
    delete particleCollision;
    particleCollision = nullptr;
}


void MainDemo::display()
{
    Application::display();

    // Draw Particles
    for (int i = 0; i < PLATFORM_COUNT; ++i) {
        glBegin(GL_LINES);
        glColor3f(0, 1, 1);
        glVertex2f(platforms[i]->start.x, platforms[i]->start.y);
        glVertex2f(platforms[i]->end.x, platforms[i]->end.y);
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

void MainDemo::update()
{
    // Recenter the axes
    float duration = timeinterval / 1000;

    // Run the simulation
    world.runPhysics(duration);

    Application::update();
}

const char* MainDemo::getTitle()
{
    return "PARTICLE COLLISION AND RESOLUTION SYSTEM USING SWEEP AND PRUNE";
}