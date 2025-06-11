#include <stdlib.h>
#include <GL/glut.h>

static GLfloat spin = 0.0;

void display(void)
{
	int r, g, b;
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	glClear(GL_COLOR_BUFFER_BIT);

	// �߿�
	glPushMatrix(); // ���� ex)�ڵ��� ���� �����ſ� ��� �Ȱ����� ������ �� ��
	//              x��  y��  z��
	glRotatef(spin, 0.0, 0.0, 1.0); // �߿� spin �̶�� ���� ������ ȸ����Ű��� ��, ������ �������� ���� (���� �ڵ��� ��� 0, 0 �� ����)
	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
	glRectf(-25.0, -25.0, 25.0, 25.0); // �簢�� �׸��� durld
	glPopMatrix(); // ����

	glutSwapBuffers(); // ���� ���۸� ��� �� flush() ��ſ� �̰� ����ؾ��� �߿�!
}

void spinDisplay(void)
{
	spin = spin + 0.5; // 0.5 �� �� ȸ��
	if (spin > 360.0)spin = spin - 360.0; // 360�� �� ���ư��� �ٽ� 0���� ����
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // ������ ����� ���������� ����
	glShadeModel(GL_FLAT); // Flat Shading���� ����
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0); // 3D Ortho
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // ���� ���۸����� ����
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("02_4 �簢�� ȸ��");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}