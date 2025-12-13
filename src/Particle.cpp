#include "particle.h"
#include <math.h>



float Particle::getRadius() const
{
    return radius;
}

void Particle::integrate(float duration) {
    position += velocity * duration;
}

void Particle::setRadius(const float r)
{
    radius = r;
}

void Particle::setPosition(const float x, const float y)
{
    position.x = x;
    position.y = y;
}


Vector2 Particle::getPosition() const
{
    return position;
}

void Particle::setVelocity(const float x, const float y)
{
    velocity.x = x;
    velocity.y = y;
}

Vector2 Particle::getVelocity() const
{
    return velocity;
}