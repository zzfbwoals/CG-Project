#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH); // �������� ���� �κ��� ���� �ڿ������� ĥ����, �� ������ ���� �ε巴�� ȥ���Ͽ� ������ <=> flat
}

void triangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(5.0, 5.0); // x=5 y=5 ��ġ�� ������ ĥ�ϱ�
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(25.0, 5.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(5.0, 25.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	triangle();
	glFlush();
}

// reshape �� ���� �����츦 ���η� �� �ø��� �غ��� �ø���ŭ �þ�ߵǴµ� ���� ���� ���� ����
// ������ â�� ũ�� ���� �� �ص� ���� ���� ����
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ȭ�鿡 �Ѹ� ��ȭ��, gluOrtho()�� ���ؼ� �����ؾ��� *******************
	// 3ds max viewport(alt+w) ��� ����
	// w, h ������ �ñ��ϸ� ������ �غ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Without Reshape recalculation
	//gluOrtho2D(0.0, 30.0, 0.0, 30.0);
	// ���� �ּ� ���ְ� �ؿ��� �ּ� ó�� �ϸ� ������ ���� ũ�⸦ ���������� ����

	// ������ ���� ũ�⸦ �������ִ� �κ� ���� �߿�**************************
	// With Reshape recalculation
	if (w <= h) // ���̰� �ʺ񺸴� �� ũ�ų� ���� ���
		// gluOrtho2D(left, right, bottom, top) �� ����
		gluOrtho2D(0.0, 30.0, 0.0, 30.0 * (float)h / (float)w); // ũ�� ����
	else // �ʺ� ���̺��� �� ū ���
		gluOrtho2D(0.0, 30.0 * (float)w / (float)h, 0.0, 30.0); // ũ�� ����
	
	glMatrixMode(GL_MODELVIEW); // �Ƚᵵ ����Ʈ�� ���� ��
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]); // ������ ����
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape); // Reshape callback function ���
	glutMainLoop();
	return 0;
}