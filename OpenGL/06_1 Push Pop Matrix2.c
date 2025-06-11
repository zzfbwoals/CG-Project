#include <GL/glut.h>

void draw_square() {
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.1);
	glVertex2f(-0.1, -0.1);
	glVertex2f(0.1, -0.1);
	glVertex2f(0.1, 0.1);
	glEnd();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0); // ������
	draw_square();

	glPushMatrix(); // Push

	glColor3f(0, 1, 0); // ���
	glTranslatef(-0.4, -0.3, 0); // �̵�
	glScalef(1.5, 1.5, 1.0);
	draw_square();

	glPopMatrix(); // Pop

	glColor3f(0, 0, 1); // �Ķ���
	glTranslatef(0.0, -0.5, 0); // �̵�
	glRotatef(45, 0.0, 0.0, 1.0); // ȸ��
	glScalef(1.5, 1.5, 1.0);
	draw_square();

	glColor3f(1.0, 0.0, 1.0); // ��ȫ��
	glTranslatef(0.3, -0.1, 0); // �̵�
	draw_square();

	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // ����
	glColor3f(1.0, 1.0, 1.0); // ���� ��

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glViewport(0, 0, 400, 400);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Push Pop Matrix");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}