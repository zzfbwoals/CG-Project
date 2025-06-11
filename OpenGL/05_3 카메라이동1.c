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
	// 5�� �����ϸ� �Ÿ��� �־����� �۰� ����. glFrustum()����ؼ� ����.
	gluLookAt(0.0, 0.0, 5.0,    // ī�޶� ��ġ (0, 0, 2)
		0.0, 0.0, 0.0,    // ��� ���� (0, 0, 0)
		0.0, 1.0, 0.0);   // up ���� (0, 1, 0) ��Ȯ�� �����ؾ���.

	//glRotatef(90.0, 1.0, 0.0, 0.0); // ī�޸��� ��ġ�� x���� �������� 90�� ȸ��
	//glTranslatef(0.0, 0.0, -2.0); // z������ -2.0��ŭ �̵�. (��ü�� �۾���)
	glutWireTeapot(1.0); // ���� �׸���.

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // ��� �ʱ�ȭ
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // ���� ���� ��ȯ
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformation Teapot");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}