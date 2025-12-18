// sphereJK_OO.cpp
// draw a single sphere in the middle of the screen
// OO basic

#include <gl/glut.h>// OpenGL toolkit
#include <app.h>// OpenGL toolkit
#include "particle.h"
#include <iostream> 
#include <string>

static constexpr int NO_OF_PARTICLES = 3;

class SphereDemo : public Application
{
	Particle particles[NO_OF_PARTICLES];
public:
	SphereDemo();
	virtual void display();
	virtual void update();
	/*
	* Method to deflect the particle off the box boundary on collision
	*
	* @param p Represents the particle
	*
	* @param boundaryWidth Represents the viewport width
	*
	* @param boundaryHeight Represents the viewport height
	*/
	void box_boundary_collision_resolve(Particle& p, int boundaryWidth, int boundaryHeight);
	/*
	* Detect particle viewport collision
	*
	Apparently in graphics libraries the top-left is the (x=0,y=0) coordinate, not the center of the viewport.
	*
	* @param p Represents the particle
	*
	* @param boundaryWidth Represents the viewport width
	*
	* @param boundaryHeight Represents the viewport height
	*
	* @return `bool` hit
	*/
	bool out_of_box_test(Particle p, int boundaryWidth, int boundaryHeight);
	/*
	* Method to draw out of bound particles within boundaries
	*
	* @param p Represents the particle
	*
	* @param boundaryWidth Represents the viewport width
	*
	* @param boundaryHeight Represents the viewport height
	*/
	void out_of_box_resolve(Particle& p, int boundaryWidth, int boundaryHeight);
};


SphereDemo::SphereDemo()
{
	// the starting width and heigh of th indow should always be 100
	width = 100; height = 100;

	//for (Particle& p : particles) {
	for (int i = 0; i < sizeof(particles) / sizeof(Particle); ++i) {
		Particle& p = particles[i];

		p.setRandomColor();
		p.setVelocity(0, 0);
		p.setAcceleration(0, 0);

		if ((i + 1) == 3) {
			p.setRadius(15);
			p.setMass(p.computeMassFromRadius(p.getRadius()));
			p.setPosition(width - (p.getRadius() + 1), height - (p.getRadius() + 1));
		}
		else if ((i + 1) == 2) {
			p.setRadius(10);
			p.setMass(p.computeMassFromRadius(p.getRadius()));
			p.setPosition(0, height - (p.getRadius() + 1));
		} 
		else {
			p.setRadius(30);
			p.setMass(p.computeMassFromRadius(p.getRadius()));
			p.setPosition(-width + (p.getRadius() + 1), height - (p.getRadius() + 1));
		}

		//if ((i + 1) != 2) {
		//p.setRadius(10);
		//p.setMass(1);
		//p.setPosition(width - (p.getRadius() + 1), height - (p.getRadius() + 1));
		//}
		//else {
		//p.setRadius(20);
		//p.setMass(5);
		//p.setPosition(-width + (p.getRadius() + 1), height - (p.getRadius() + 1));
		//}


		//p.setRandomRadius(width, height);
		//p.setRandomColor();
		//p.setRandomPosition(p.getRadius(), width, height);
		//p.setRandomVelocity(static_cast<float>(width));
	}
}

bool SphereDemo::out_of_box_test(Particle p, int boundaryWidth, int boundaryHeight) {
	Vector2 pos = p.getPosition();
	float r = p.getRadius();

	if (pos.x - r < -boundaryWidth) return true; // leftmost particle point outside with boundary
	if (pos.x + r > boundaryWidth) return true; // rightmost particle point outside with boundary
	if (pos.y - r < -boundaryHeight) return true; // bottommost particle point outside with boundary
	if (pos.y + r > boundaryHeight) return true; // topmost particle point outside with boundary

	return false;
}

void SphereDemo::box_boundary_collision_resolve(Particle &p, int boundaryWidth, int boundaryHeight) {
	Vector2 pos = p.getPosition();
	Vector2 pv = p.getVelocity();
	float r = p.getRadius();

	// leftmost & rightmost particle point collision with box boundary
	if (pos.x - r <= -boundaryWidth || pos.x + r >= boundaryWidth) {
		pv.x = -pv.x;
	}
	// topmost & bottommost particle point collision with box boundary 
	if (pos.y - r <= -boundaryHeight || pos.y + r >= boundaryWidth) {
		pv.y = -pv.y;
	}
	p.setVelocity(pv.x, pv.y);
}

void SphereDemo::out_of_box_resolve(Particle &p, int boundaryWidth, int boundaryHeight) {
	Vector2 pos = p.getPosition();
	float r = p.getRadius();
	// Clamp X
	if (pos.x - r < -boundaryWidth) pos.x = -boundaryWidth + r; // push back inside
	if (pos.x + r > boundaryWidth) pos.x = boundaryWidth - r;

	// Clamp Y
	if (pos.y - r < -boundaryHeight) pos.y = -boundaryHeight + r;
	if (pos.y + r > boundaryHeight) pos.y = boundaryHeight - r;

	p.setPosition(pos.x, pos.y);
}

void SphereDemo::update(void)
{	
	for (Particle& p : particles) {
		float duration = timeinterval / 1000;
		
		p.addForce(p.getGravityForce());
		Vector2 drag = p.getDragForce();
		std::cout << "radius: " + std::to_string(p.getRadius()) + " mass: " + std::to_string(p.getMass()) + " bottompos: " + std::to_string(p.getPosition().y - p.getRadius()) + " speed: " + std::to_string(p.getVelocity().magnitude()) << "drag x: " << drag.x << " drag y: " << drag.y << std::endl;
		p.addForce(drag);
		
		p.integrate(duration);
		box_boundary_collision_resolve(p, width, height);
		if (out_of_box_test(p, width, height)) {
			out_of_box_resolve(p, width, height);
		}
	}
	Application::update();
}

void SphereDemo::display(void)
{
	Application::display();

// To prevent accumulation of translations we reset the matrix for each particle
	for (Particle& p : particles) {
		glPushMatrix();
		Vector2 position = p.getPosition();
		customcolor::Color pcolor = p.getColor();
		glTranslatef(position.x, position.y, 0.0f);
		glColor3ub(pcolor.r, pcolor.g, pcolor.b);
		glutSolidSphere(p.getRadius(), 30, 30);
		glPopMatrix();
	}

	glutSwapBuffers();
}

Application* getApplication()
{
    return new SphereDemo();
}






