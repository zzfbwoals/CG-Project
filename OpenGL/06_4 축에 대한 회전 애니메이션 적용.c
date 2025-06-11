#include <stdio.h>
#include <GL/glut.h>

float y_position;
int flag;
float rotation; // ȸ�� ����

void init()
{
	y_position = 0.0;
	flag = 0;
	rotation = 0.0;
}

void draw_axis()
{
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_LINES); // x�� ����
	glVertex2f(-1.0, 0.0);
	glVertex2f(11.0, 0.0);
	glEnd();

	glBegin(GL_LINES); // y�� ����
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 11.0);
	glEnd();
}

void draw_basic_axis_line()
{
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES); // �⺻ x�� ���� (y ��ġ�� ��)
	glVertex2f(0.0, y_position);
	glVertex2f(10.0, y_position);
	glEnd();
}

void draw_triangle()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(5.0, 6.0); // ���� ��
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(4.0, 4.0); // ���� ��
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(6.0, 4.0); // ������ ��
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_basic_axis_line();

	if (flag)
	{
		// y_position�� �������� ȸ��
		glTranslatef(0.0, y_position, 0.0);
		glRotatef(rotation, 1.0, 0.0, 0.0); // 5���� �����ϴ� ȸ��
		glTranslatef(0.0, -y_position, 0.0);
	}

	draw_triangle();

	glFlush();
}

void idle()
{
	if (flag)
	{
		rotation += 0.1; // 5���� ����
		if (rotation >= 360.0)
			rotation -= 360.0;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		flag = 1; // ȸ�� �ִϸ��̼� ����
		glutIdleFunc(idle); // idle �Լ� ���
		break;

	case 'p':
		exit(0);
		break;

	default:
		break;
	}
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		y_position = y_position + 0.1;
		glutPostRedisplay();
		flag = 0;
		glutIdleFunc(NULL); // �ִϸ��̼� ����
	}
	if (key == GLUT_KEY_DOWN)
	{
		y_position = y_position - 0.1;
		glutPostRedisplay();
		flag = 0;
		glutIdleFunc(NULL); // �ִϸ��̼� ����
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 11.0, -1.0, 11.0, -1.0, 1.0);
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Axis-based Rotation");

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutSpecialFunc(SpecialKeys);

	glutMainLoop();

	return 0;
}
