#include <stdlib.h>
#include <GL/glut.h>

float v1[3] = { 75.0, 400.0, 0.0 }; // ù��° ���� ��ġ
float v2[3] = { 150.0, 100.0, 0.0 }; // �ι�° ���� ��ġ
float v3[3] = { 225.0, 400.0, 0.0 }; // ����° ���� ��ġ
float v4[3] = { 300.0, 100.0, 0.0 }; // �׹�° ���� ��ġ
float v5[3] = { 375.0, 400.0, 0.0 }; // �ټ���° ���� ��ġ
float v6[3] = { 450.0, 100.0, 0.0 }; // ������° ���� ��ġ

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// ���������� ���� �׸��� �ڵ�
void draw_points()
{
	glColor3f(1.0, 0.0, 0.0); // ������

	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// ������� ��(lines)�� �׸��� �ڵ�
void draw_lines()
{
	glColor3f(0.0, 1.0, 0.0); // ���
	glBegin(GL_LINES);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// ������� ��(line strip)�� �׸��� �ڵ�
void draw_lines_strip()
{
	glColor3f(0.0, 1.0, 0.0); // ���
	glBegin(GL_LINE_STRIP);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// ������� �ﰢ��(traingle fan)�� �׸��� �ڵ�
void draw_triangle_fan()
{
	glColor3f(0.0, 1.0, 0.0); // ���

	// ������ ����
	glBegin(GL_TRIANGLE_FAN);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// ������� �簢��(quads)�� �׸��� �ڵ�
void draw_quads()
{
	glColor3f(0.0, 1.0, 0.0); // ���

	// ������ ����
	glBegin(GL_QUADS);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v4);
	glVertex3fv(v3);
	glEnd();
}

// ������� �簢��(quad strip)�� �׸��� �ڵ�
void draw_quad_strip()
{
	glColor3f(0.0, 1.0, 0.0); // ���

	// ������ ����
	glBegin(GL_QUAD_STRIP);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// ������� �ٰ���(polygon)�� �׸��� �ڵ�
void draw_polygon()
{
	glColor3f(0.0, 1.0, 0.0); // ���

	// ������ ����
	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v4);
	glVertex3fv(v6);
	glVertex3fv(v5);
	glVertex3fv(v3);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_points();
	//draw_lines();
	//draw_lines_strip();
	//draw_lines_loop();
	//draw_triangle();
	//draw_triangle_strip();
	//draw_triangle_fan(); // 123, 145, 156 ���� �׷���
	//draw_quads();
	//draw_quad_strip();
	//draw_polygon();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My Fisrt Gl Program");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}