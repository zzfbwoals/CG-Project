#include <GL/glut.h>

// viewport ÀÇ Áß¾Ó¿¡ »ç°¢ÇüÀ» ±×¸®´Â ÇÔ¼ö
void draw_square()
{
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// »¡°­»öÀ¸·Î °¢ view portÀÇ °æ°è¸¦ Ç¥½Ã
	glViewport(0, 0, 400, 400); // ½ÃÀÛÀ§¯M(GLint x, GLint y), ³Êºñ ³ôÀÌ(GLsizei width, ? GLsizei height)
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0);
	glVertex2f(1.0, 0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	// ÁÂÇÏ´Ü ºÎºÐÀ» view port·Î È°¿ëÇÏ¿© ³ì»öÀ¸·Î »ç°¢ÇüÀ» ±×¸²
	glViewport(0, 0, 200, 200);
	glColor3f(0.0, 1.0, 0.0);
	draw_square();

	// ÁÂ»ó´Ü ºÎºÐÀ» view port·Î È°¿ëÇÏ¿© ÇÎÅ©»öÀ¸·Î »ç°¢ÇüÀ» ±×¸²
	glViewport(0, 200, 200, 200);
	glColor3f(1.0, 0.0, 1.0);
	draw_square();

	// ¿ìÇÏ´Ü ºÎºÐÀ» view port·Î È°¿ëÇÏ¿© ÇÎÅ©»öÀ¸·Î »ç°¢ÇüÀ» ±×¸²
	glViewport(200, 0, 200, 200);
	glColor3f(1.0, 1.0, 0.0);
	draw_square();

	// ¿ì»ó´Ü ºÎºÐÀ» view port·Î È°¿ëÇÏ¿© ÇÎÅ©»öÀ¸·Î »ç°¢ÇüÀ» ±×¸²
	glViewport(200, 200, 200, 200);
	glColor3f(0.0, 0.0, 1.0);
	draw_square();

	glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("glViewport Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}