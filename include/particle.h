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
	 //Vector2 acceleration;
    // float damping;
	 float radius;
	 customcolor::Color color;
	 
      public:
        void setPosition(const float x, const float y);
		void setRadius(const float r);
		Vector2 getPosition() const;
		float getRadius() const;
		void integrate(float duration);

		void setVelocity(const float x, const float y);
		Vector2 getVelocity() const;

		////void setAcceleration(const float x, const float y);
		////Vector2 getAcceleration() const;
	    //void setDamping(const float damping);
         //     float getDamping() const;

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
		* @breif Assign a random velocity to the particle
		* 
		* @parma maxVelocity Represents the absolute maximum and minimum velocity of the particle
		*/
		void setRandomVelocity(float maxVelocity);
       };

	#endif 