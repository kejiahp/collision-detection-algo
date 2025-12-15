#include "particle.h"
#include <math.h>
#include "utils.hpp"
#include <iostream>

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

void Particle::setColor(const customcolor::Color &newColor) {
    color = newColor;
}

void Particle::setRandomColor() {
    setColor(customcolor::random_rgb());
};

customcolor::Color Particle::getColor() const {
    return color;
};

void Particle::setRandomRadius(int boundW, int boundH) {
    // find the smallest boundary value
    int smallestBoundary = boundW > boundH ? boundH : boundW;
    // check if 1/4 the smallest boundary is gte to 10
    int rangeMin = smallestBoundary / 4 >= 10 ? 10 : 1;
    setRadius(static_cast<float>(utils::random_in_range(rangeMin, smallestBoundary / 2)));
};


void Particle::setRandomPosition(float radius, int boundW, int boundH) {
    boundW = boundW - radius;
    boundH = boundH - radius;
    float x = static_cast<float>(utils::random_in_range(-boundW, boundW));
    float y = static_cast<float>(utils::random_in_range(-boundH, boundH));
    setPosition(x, y);
}

void Particle::setRandomVelocity(float maxVelocity) {
    float x = static_cast<float>(utils::random_in_range(-maxVelocity, maxVelocity));
    float y = static_cast<float>(utils::random_in_range(-maxVelocity, maxVelocity));
    setVelocity(x, y);
};