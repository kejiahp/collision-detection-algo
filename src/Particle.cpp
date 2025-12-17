#include <math.h>
#include <assert.h>

#include "particle.h"
#include "utils.hpp"

float Particle::getRadius() const
{
    return radius;
}

void Particle::integrate(float duration) {
    assert(duration > 0.0);
    if (inverseMass <= 0.0f) return;

    // work out the acceleration from the force
    Vector2 resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);

    // update linear velocity from the acceleration
    velocity.addScaledVector(resultingAcc, duration);

    // impose drag
    //velocity *= pow(damping, duration);
    
    // update linear position
    position.addScaledVector(velocity, duration);

    // clear the forces
    clearAccumulator();
}

Vector2 Particle::getDragForce() {
    float speed = velocity.magnitude();
    if (speed <= 0.0f) return Vector2{0, 0}; // no drag needed
    float k1 = 0.0;
    float k2 = 0.01 * radius * radius;
    float dragMag = k1 * speed + k2 * speed * speed;
    Vector2 dragForce;
    // direction of drag = opposite of velocity direction
    dragForce.x = velocity.x * -(dragMag / speed);
    dragForce.y = velocity.y * -(dragMag / speed); 
    return dragForce;
}


float Particle::computeMassFromRadius(float radius, float refRadius, float refMass) {
    float scale = radius / refRadius;
    return refMass * scale * scale * scale;
}

Vector2 Particle::getGravityForce() const {
    return Vector2(0, -10 * getMass());
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

void Particle::setAcceleration(const Vector2& newAcceleration) {
    acceleration = newAcceleration;
}

void Particle::setAcceleration(const float x, const float y) {
    acceleration.x = x;
    acceleration.y = y;
}

Vector2 Particle::getAcceleration() const {
    return acceleration;
}

void Particle::setDamping(const float damping) {
    this->damping = damping;
}

float Particle::getDamping() const {
    return damping;
}

void Particle::setMass(const float mass) {
    assert(mass != 0);
    inverseMass = 1.0 / mass;
}

float Particle::getMass() const {
    if (inverseMass == 0) {
        return DBL_MAX;
    }
    else {
        return 1.0 / inverseMass;
    }
}

void Particle::setInverseMass(const float inverseMass) {
    this->inverseMass = inverseMass;
}

float Particle::getInverseMass() const {
    return inverseMass;
}

bool Particle::hasFiniteMass() const {
    return inverseMass >= 0.0f;
}

void Particle::clearAccumulator() {
    forceAccum.clear();
}

void Particle::addForce(const Vector2& force) {
    forceAccum += force;
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