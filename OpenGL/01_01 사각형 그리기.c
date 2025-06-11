#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void display(void) 
{
	glColor3f(1.0, 1.0, 1.0); // ������� ����

	// �簢���� ��ǥ �Է�
	glBegin(GL_POLYGON);
		// �� 4�� ��ǥ (�簢��) xyz
		glVertex3f(0.25, 0.25, 0.0); // ���� �ڽ��� 0~1 �� ũ�⿩�� 0.25 0.75�� ��ǥ�� �� ����. gl->�����Լ� 3->�Ķ���ͼ� f->�ε��Ҽ�
		glVertex3f(0.75, 0.25, 0.0); 
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glFlush(); // �簢���� ȭ�鿡 �׸�
	printf("glutDisplayFunc(display)\n");
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // ������ ����� ���������� ���� (0~1)
	glClear(GL_COLOR_BUFFER_BIT); // ���� ���۸� ����
	glMatrixMode(GL_PROJECTION); // ������ ��ĵ��� Projection ��� ���ÿ� ����
	glLoadIdentity(); // ���� ���(�밢���� 1�� ���)�� �ʱ�ȭ

	// ���� ����: left, right, bottom, top, near, far
	// �߿��մϴ�**************
	// �����ڽ� �ۿ� �׸� �׸��� �ȳ���
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) // argc, argv �Ű�����: ������ �� �� ����� �޾Ƽ� �� ����� �� �� �ִ� <- ���Ҹ���... ������ ����
{
	glutInit(&argc, argv); // GLUT ���¸� �ʱ�ȭ, �ٸ� glut �Լ��� ���� �׻� �� ����
	// ���÷��� ������� ����: Single buffer & RGBA color ��� ����, 3�� ���� ����� �ϳ� 3�� ���� ����� �ϳ� ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// â�� ũ��� ��ġ ����
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("01 �簢�� �׸���"); // ���������, ID�� ���������� ���ϵȴ�.
	init();

	// �ʿ��� �ݹ��Լ� ���
	// â�� ���Ȯ�� �̵� �� �Ҷ����� ��� �Լ��� �ݹ� �ȴ�.
	glutDisplayFunc(display);
	glutMainLoop(); // �̺�Ʈ ó�� ���� ����, �������� �׻� �־�� ��

	return 0;
}