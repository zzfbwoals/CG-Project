#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // ��� �ʱ�ȭ

	// Viewing Transformation
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 0.0); // ������
	glutWireCube(1.0);

	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);; // ���
	glTranslatef(-1.5, 0.0, 1.5); // ��ü�� �̵��� ���� ��ȭ ����
	glutWireCube(1.0);

	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0); // �Ķ���
	glTranslatef(1.5, 0.0, 1.5); // ��ü�� �̵��� ���� ��ȭ Ȯ��
	glutWireCube(1.0);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // ��� �ʱ�ȭ
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // ���� ���� Ȯ��
	//glOrtho(-7.0, 7.0, -7.0, 7.0, 1.5, 20.0); // ���� ���� Ȯ��
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("���� ��� ����");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}