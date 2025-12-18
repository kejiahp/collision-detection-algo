    /**
     * A particle is the simplest object that can be simulated in the
     * physics system.

     */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "coreMath.h"
#include "custom_color.hpp"

class Particle
    {
    protected:
     Vector2 position;
	 Vector2 velocity;
	 Vector2 acceleration;
	 Vector2 forceAccum;  // Represents the accumulation of the various forces acting on the particle e.g. gravity
     float damping; // Don't use this, use the `getDragForce` method, add the returned force to the accumulator on each render
	 float radius;
	 float inverseMass;
	 customcolor::Color color;
	 
      public:
        void setPosition(const float x, const float y);
		void setRadius(const float r);
		Vector2 getPosition() const;
		float getRadius() const;
		void integrate(float duration);

		void setVelocity(const Vector2& velocity);
		void setVelocity(const float x, const float y);
		Vector2 getVelocity() const;

		void setAcceleration(const Vector2& newAcceleration);
		void setAcceleration(const float x, const float y);
		Vector2 getAcceleration() const;

		/**
		* @brief Clear the D'Alembert accumulator
		*/
		void clearAccumulator();

		/**
		* @brief Adds a force to the D'Alembert accumulator
		*/
		void addForce(const Vector2& force);

		/**
		* @brief Calculate and return the drag force acting on the particle.
		* 
		* The drag magnitude is calculated using this formula `Fdrag = -k1 * |V| - k2 * |V|^2`
		* 
		* @return `Vector2` the drag force.
		*/
		Vector2 getDragForce();

		/**
		* // Don't use this, use the `getDragForce` method, add the returned force to the accumulator on each render.
		* 
		* @brief Set the damping force simulation air resistance
		* 
		* @param damping the dampling value within the range of 0-1. The lower the value, the more damping force.
		*/
	    void setDamping(const float damping);

		/**
		* // Don't use this, use the `getDragForce` method, add the returned force to the accumulator on each render.
		* 
		* @brief Get the damping force
		*/
        float getDamping() const;

		void setMass(const float mass);
		float getMass() const;
		void setInverseMass(const float inverseMass);
		float getInverseMass() const;
		bool hasFiniteMass() const;

		/**
		* @brief Returns the gravitational force acting on a particle, considering the mass of the object.
		*/
		Vector2 getGravityForce() const;

		/**
		* @brief Set the particles color
		*
		* @param color The particles color
		*/
		void setColor(const customcolor::Color& color);
		/**
		* @brief Assign a random color to a particle
		*/
		void setRandomColor();
		/**
		* @brief Get the color assigned to a particle
		*/
		customcolor::Color getColor() const;
		/**
		* @brief Assign a random radius to the particle, ensures the random radius is less than 1/4 the smallest boundary value
		* 
		* @param boundW Represents the viewport width
		*
		* @param boundH Represents the viewport height
		*/
		void setRandomRadius(int boundW, int boundH);
		/**
		* @brief Assign a random position within the window boundary to the particle
		* 
		* @param boundW Represents the viewport width
		*
		* @param boundH Represents the viewport height
		*/
		void setRandomPosition(float radius, int boundW, int boundH);

		/**
		* @brief Assign a random velocity to the particle
		* 
		* @param maxVelocity Represents the absolute maximum and minimum velocity of the particle
		*/
		void setRandomVelocity(float maxVelocity);

		/**
		* Due to potential physical inconsistencies in the mass and radius of a particle, we can calculate the mass from a given radius and reference sphere.
		*
		* Example: If you give a big sphere a large radius but only slightly increase its mass,
		* it will experience too much drag for its weight, and fall slower than expected.
		* 
		* @param radius the particle radius
		* @param refRadius optional - reference particles radius
		* @param refMass optional - reference particles mass
		*/
		float computeMassFromRadius(float radius, float refRadius = 5, float refMass = 1);
       };

	#endif 