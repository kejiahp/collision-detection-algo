// sphereJK_OO.cpp
// draw a single sphere in the middle of the screen
// OO basic

#include <gl/glut.h>// OpenGL toolkit
#include <app.h>// OpenGL toolkit
#include "particle.h"
#include <iostream> 


using namespace std;
class SphereDemo : public Application
{
	Particle particles[2];
public:
	SphereDemo();
	virtual void display();
	virtual void update();
};


SphereDemo::SphereDemo()
{
	for (int i = 0; i < sizeof(particles) / sizeof(Particle); ++i) {
		Particle& p = particles[i];
		if ((i + 1) % 2 == 0) {
			p.setPosition(10, 50);
			p.setRadius(10 * (i + 1));
		}
		else {
			p.setPosition(0, 0);
			p.setRadius(10);
		}
		p.setVelocity(-6, 9);
	}
	// the starting width and heigh of th indow should always be 100
	width = 100; height = 100;
}

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
bool hitBoxBoundary(const Particle& p, int boundaryWidth, int boundaryHeight) {
	Vector2 pos = p.getPosition();
	float r = p.getRadius();

	if (pos.x - r <= -boundaryWidth) return true; // leftmost particle point collision with boundary
	if (pos.x + r >= boundaryWidth) return true; // rightmost particle point collision with boundary
	if (pos.y - r <= -boundaryHeight) return true; // topmost particle point collision with boundary
	if (pos.y + r >= boundaryHeight) return true; // bottommost particle point collision with boundary

	return false;
}

void onboundaryHit(Particle &p, int boundaryWidth, int boundaryHeight) {
	Vector2 pos = p.getPosition();
	Vector2 pv = p.getVelocity();
	int r = p.getRadius();

	if (pos.x - r <= -boundaryWidth || pos.x + r >= boundaryWidth) {
		pv.x = -pv.x;
	}
	if (pos.y - r <= -boundaryHeight || pos.y + r >= boundaryWidth) {
		pv.y = -pv.y;
	}
	p.setVelocity(pv.x, pv.y);
}

void SphereDemo::update(void)
{	
	for (Particle& p : particles) {
		if (hitBoxBoundary(p, width, height)) {
			onboundaryHit(p, width, height);
		}
		float duration = timeinterval / 1000;
		p.integrate(duration);
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
		glTranslatef(position.x, position.y, 0.0f);
		glColor3ub(255, 0, 0);
		glutSolidSphere(p.getRadius(), 30, 30);
		glPopMatrix();
	}

	glutSwapBuffers();
}

Application* getApplication()
{
    return new SphereDemo();
}






