#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define size 50.0

float w_height = 800;
float w_width = 800;
float square_x = 0, square_y = 400; // position of square
float square_dx = 0.5; // incremental change insquare_x

void idleCallBack()
{
	square_x += square_dx; // increment x-psotion of square
	if (square_x + size > w_width || square_x <= 0) square_dx *= -1.0; // Reverse direction if at deges
	glutPostRedisplay();
}

void displayCallBack(void)
{
	// set Clear color to black and clear window
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// set Projection Mode and Volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w_width, 0.0, w_height, -1.0, 1.0); // 윈도우 크기에 맞춰서 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(square_x, square_y, 0.0);

	glColor3ub(255, 255, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(size, 0);
	glVertex2f(size, size);
	glVertex2f(0, size);
	glEnd();
}

void main(int argc, char** argv)
{
	// Allow cmd line arguments to be passed to the glut
	glutInit(&argc, argv);

	// Create and name window
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(w_width, w_height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Idle Callback");

	// Set up callbacks
	glutDisplayFunc(displayCallBack);
	glutIdleFunc(idleCallBack);

	// Enter main event loop
	glutMainLoop();
}