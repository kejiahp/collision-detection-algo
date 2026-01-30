#ifndef MAIN_DEMO_H
#define MAIN_DEMO_H

#include <gl/glut.h>
#include <stdio.h>
#include <utility>
#include <cassert>

#include "app.h"
#include "coreMath.h"
#include "pcontacts.h"
#include "pworld.h"
#include "pcollision.h"
#include "pplatform.h"


class MainDemo : public Application
{
    Particle* blobs;

    Platform** platforms;

    ParticleCollision* particleCollision;

    ParticleWorld world;

public:
    /** Creates a new demo object. */
    MainDemo();
    virtual ~MainDemo();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particles. */
    virtual void display();

    /** Update the particle positions. */
    virtual void update();

};

#endif // 