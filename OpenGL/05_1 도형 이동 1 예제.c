#include <GL/glut.h>
#include <stdlib.h>

float v1[3] = { -10.0, -35.0, 0.0 }; // 첫번쨰 정점 위치
float v2[3] = { 10.0, -35.0, 0.0 }; // 두번쨰 정점 위치
float v3[3] = { 10.0, 35.0, 0.0 }; // 세번쨰 정점 위치
float v4[3] = { -10.0, 35.0, 0.0 }; // 네번쨰 정점 위치

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 400.0, -100.0, 400.0);
}

// 사각형을 그리는 코드
void draw_rectangle(void)
{
	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glEnd();
}

void draw_line()
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-100.0, 0.0, 0.0);
	glVertex3f(400.0, 0.0, 0.0);
	glVertex3f(0.0, -100.0, 0.0);
	glVertex3f(0.0, 400.0, 0.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	draw_line();
	
	glColor3f(0.0, 0.0, 1.0); // Blue Color
	draw_rectangle();

	// Rotate 45 degree and then translate 100 to x direction 원점기준 회전하고 이동
	glLoadIdentity();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(100.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0); // Red Color
	draw_rectangle();

	// Translate 100 to x direction and then rotate 45 degree 이동하고 원점기준 회전
	glLoadIdentity();
	glRotated(45.0, 0.0, 0.0, 1.0);
	glTranslatef(100.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0); // Yellow Color
	draw_rectangle();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Object TransFormation Program");
	init();

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}