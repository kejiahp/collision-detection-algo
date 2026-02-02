#include <gl/glut.h>

#include "main_demo.h"

static MainDemo app;

static void display(void)
{
	app.display();
}


static void TimerFunc(int value)
{
	app.update();
	float  timeinterval = app.getTimeinterval();
	glutTimerFunc(timeinterval, TimerFunc, 1);
}

static void createWindow(const char* title, int h, int w)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(h, w);
    glutCreateWindow(title);
}


static void resize(int width, int height)
{
    app.resize(width, height);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	float  timeinterval = 10;

	app.setTimeinterval(timeinterval);

	createWindow(app.getTitle(), app.getheight(), app.getwidth());

	glutReshapeFunc(resize);

	glutDisplayFunc(display); 

	glutTimerFunc(timeinterval, TimerFunc, 1);

	app.initGraphics();

	glutMainLoop();

	return 0;
}