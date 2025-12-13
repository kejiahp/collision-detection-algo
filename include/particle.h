    /**
     * A particle is the simplest object that can be simulated in the
     * physics system.

     */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "coreMath.h"

class Particle
    {
    protected:
     Vector2 position;
	 Vector2 velocity;
	 //Vector2 acceleration;
    // float damping;
	 float radius;

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

       };

	#endif 