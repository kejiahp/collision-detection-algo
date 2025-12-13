#include <gl/glut.h>

#include "app.h"
extern Application* getApplication();
Application* app;


void display(void)
	{
	app->display();
	}


void TimerFunc(int value)
{
	app->update();
	float  timeinterval = app->getTimeinterval();
	glutTimerFunc(timeinterval, TimerFunc, 1);
}

void createWindow(const char* title)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow(title);
}


void resize(int width, int height)
{
    app->resize(width, height);
}

int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    app = getApplication();
	float  timeinterval = 5;
	app->setTimeinterval(timeinterval);
	createWindow("Sphere");
	glutReshapeFunc(resize);
	glutDisplayFunc(display); 
	glutTimerFunc(timeinterval, TimerFunc, 1);
	app->initGraphics();
	glutMainLoop();
	delete app; 
	return 0;
    }