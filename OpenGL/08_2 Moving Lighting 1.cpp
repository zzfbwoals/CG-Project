#include <stdio.h>
#include <GL/glut.h>

GLfloat position[] = { 0.0, 4.5, 0.0, 1.0 }; // ���� ��ġ ���� ����

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // ���� ����
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; // �ֺ���
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // Ȯ�걤
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // �ݻ籤

	glShadeModel(GL_SMOOTH); // ���� �� ����
	glEnable(GL_LIGHTING); // ���� Ȱ��ȭ
	glEnable(GL_LIGHT0); // ���� 0 Ȱ��ȭ
	glEnable(GL_DEPTH_TEST); // ���� �׽�Ʈ Ȱ��ȭ

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); // �ֺ��� ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // Ȯ�걤 ����
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // �ݻ籤 ����

	// ������
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.004);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ȭ�� �����
	
	// ���� �̵� ����
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, position); // ���� ��ġ ����

	// ������ ��ġ�� Cube�� ���
	glTranslated(position[0], position[1], position[2]);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.5);

	glEnable(GL_LIGHTING);
	glPopMatrix();

	glutSolidSphere(1, 50, 50);
	glFlush(); // ȭ�鿡 �׸���
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w, 5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			position[1] -= 0.1;
			printf("Light Position: (%.2lf, %.2lf, %.2lf)\n", position[0], position[1], position[2]);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			position[1] += 0.1;
			printf("Light Position: (%.2lf, %.2lf, %.2lf)\n", position[0], position[1], position[2]);
		}
		break;
	defalut:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Moving Lighting Example"); // ������ ����
	init();
	glutDisplayFunc(display); // ���÷��� �ݹ� �Լ� ���
	glutReshapeFunc(reshape); // �������� �ݹ� �Լ� ���
	glutMouseFunc(mouse); // ���콺 �ݹ� �Լ� ���
	glutMainLoop(); // �̺�Ʈ ���� ����
	return 0;
}