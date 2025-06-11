#include <stdlib.h>
#include <GL/glut.h>

float v1[3] = { 75.0, 400.0, 0.0 }; // 첫번째 정점 위치
float v2[3] = { 150.0, 100.0, 0.0 }; // 두번째 정점 위치
float v3[3] = { 225.0, 400.0, 0.0 }; // 세번째 정점 위치
float v4[3] = { 300.0, 100.0, 0.0 }; // 네번째 정점 위치
float v5[3] = { 375.0, 400.0, 0.0 }; // 다섯번째 정점 위치
float v6[3] = { 450.0, 100.0, 0.0 }; // 여섯번째 정점 위치

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// 빨강색으로 점을 그리는 코드
void draw_points()
{
	glColor3f(1.0, 0.0, 0.0); // 빨강색

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

// 녹색으로 선(lines)을 그리는 코드
void draw_lines()
{
	glColor3f(0.0, 1.0, 0.0); // 녹색
	glBegin(GL_LINES);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// 녹색으로 선(line strip)을 그리는 코드
void draw_lines_strip()
{
	glColor3f(0.0, 1.0, 0.0); // 녹색
	glBegin(GL_LINE_STRIP);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// 녹색으로 삼각형(traingle fan)을 그리는 코드
void draw_triangle_fan()
{
	glColor3f(0.0, 1.0, 0.0); // 녹색

	// 순서에 주의
	glBegin(GL_TRIANGLE_FAN);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// 녹색으로 사각형(quads)을 그리는 코드
void draw_quads()
{
	glColor3f(0.0, 1.0, 0.0); // 녹색

	// 순서에 주의
	glBegin(GL_QUADS);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v4);
	glVertex3fv(v3);
	glEnd();
}

// 녹색으로 사각형(quad strip)을 그리는 코드
void draw_quad_strip()
{
	glColor3f(0.0, 1.0, 0.0); // 녹색

	// 순서에 주의
	glBegin(GL_QUAD_STRIP);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glEnd();
}

// 녹색으로 다각형(polygon)을 그리는 코드
void draw_polygon()
{
	glColor3f(0.0, 1.0, 0.0); // 녹색

	// 순서에 주의
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
	//draw_triangle_fan(); // 123, 145, 156 으로 그려짐
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