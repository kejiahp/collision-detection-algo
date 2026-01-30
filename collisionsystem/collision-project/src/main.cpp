#include <gl/glut.h>

#include "main_demo.h"

MainDemo* app = new MainDemo();

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

void createWindow(const char* title, int h, int w)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(h, w);
    glutCreateWindow(title);
}


void resize(int width, int height)
{
    app->resize(width, height);
}

int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);

	float  timeinterval = 10;

	app->setTimeinterval(timeinterval);

	createWindow(app->getTitle(), app->getheight(), app->getwidth());

	glutReshapeFunc(resize);

	glutDisplayFunc(display); 

	glutTimerFunc(timeinterval, TimerFunc, 1);

	app->initGraphics();

	glutMainLoop();

	delete app; 

	return 0;
    }