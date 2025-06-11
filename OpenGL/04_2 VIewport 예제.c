#include <GL/glut.h>

// viewport �� �߾ӿ� �簢���� �׸��� �Լ�
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

	// ���������� �� view port�� ��踦 ǥ��
	glViewport(0, 0, 400, 400); // �������M(GLint x, GLint y), �ʺ� ����(GLsizei width, ? GLsizei height)
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0);
	glVertex2f(1.0, 0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	// ���ϴ� �κ��� view port�� Ȱ���Ͽ� ������� �簢���� �׸�
	glViewport(0, 0, 200, 200);
	glColor3f(0.0, 1.0, 0.0);
	draw_square();

	// �»�� �κ��� view port�� Ȱ���Ͽ� ��ũ������ �簢���� �׸�
	glViewport(0, 200, 200, 200);
	glColor3f(1.0, 0.0, 1.0);
	draw_square();

	// ���ϴ� �κ��� view port�� Ȱ���Ͽ� ��ũ������ �簢���� �׸�
	glViewport(200, 0, 200, 200);
	glColor3f(1.0, 1.0, 0.0);
	draw_square();

	// ���� �κ��� view port�� Ȱ���Ͽ� ��ũ������ �簢���� �׸�
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