#include <stdlib.h>
#include <GL/glut.h>

void init(void)
{

	// Lighting Property
	GLfloat light_position[] = { 1.0, 2.0, 3.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 1.0, 0.0, 1.0 };	// �ֺ� �ݻ籤�� ���
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };	// Ȯ�� �ݻ籤�� ������
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };	// �ݻ籤�� ���

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);	// �ε巯�� ����

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	// ���� ��ġ
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	// �ֺ� �ݻ籤
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	// Ȯ�� �ݻ籤
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	// �ݻ籤

	glEnable(GL_LIGHTING);	// ���� ���
	glEnable(GL_LIGHT0);	// ���� 0�� ���
	glEnable(GL_DEPTH_TEST);	// ���� �׽�Ʈ ���
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ȭ�� �����
	glutSolidTeapot(0.5);	// �������� �׸���
	glFlush();	// �׸���
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	// ����Ʈ ����
	glMatrixMode(GL_PROJECTION);	// ���� ��� ��� ����
	glLoadIdentity();	// ���� ��ķ� �ʱ�ȭ

	if(w<=h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);	// ���� ����
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);	// ���� ����
	glMatrixMode(GL_MODELVIEW);	// �� �� ��� ��� ����
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// GLUT �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	// ���� ����, RGB ���, ���� ���� ���
	glutInitWindowSize(500, 500);	// ������ ũ�� ����
	glutInitWindowPosition(100, 100);	// ������ ��ġ ����
	glutCreateWindow("Lighting");	// ������ ����
	init();	// �ʱ�ȭ �Լ� ȣ��

	glutDisplayFunc(display);	// ���÷��� �ݹ� �Լ� ���
	glutReshapeFunc(reshape);	// �������� �ݹ� �Լ� ���
	glutMainLoop();	// �̺�Ʈ ���� ����
	return 0;
}