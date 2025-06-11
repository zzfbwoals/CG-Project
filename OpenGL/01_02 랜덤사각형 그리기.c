#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

static int delay = 10;

void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void display()
{
	int x1, y1, x2, y2, r, g, b;

	x1 = rand() % 50; y1 = rand() % 50; x2 = rand() % 50; y2 = rand() % 50; // 0~49 의 값 -> 투영박스 범위가 0~50
	r = rand() % 256; g = rand() % 256; b = rand() % 256;

	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1); glVertex2f(x1, y2);
	glVertex2f(x2, y2); glVertex2f(x2, y1);
	glEnd();

	glFlush();
}

void timer(int t)
{
	glutPostRedisplay(); // glutDisplayFunc(display) 이 자동으로 호출
	glutTimerFunc(delay, timer, t); // 재귀호출
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog-2: Random boxes");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0); // 일정시간마다 호출

	init();
	glutMainLoop();

	return 0;
}