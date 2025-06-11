#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glFlush();
}

// ������ â �ȿ����� ������ ��.
void mouseProcess(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Left mouse button if pressed..\a\n"); // \a �� �Ҹ����� ����
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		printf("Middle mouse button if pressed..\a\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		printf("RIGHT mouse button if pressed..\a\n");
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		printf("Left mouse button if released..\a\n");
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		printf("Middle mouse button if released..\a\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		printf("RIGHT mouse button if released..\a\n");
	}
}

void mousePassivMotion(int x, int y)
{
	printf("Current mouse position: %d, %d\n", x, y);
}

void mouseActiveMotion(int x, int y)
{
	printf("Pressed mouse position: %d, %d\n", x, y);
}

void mouseEntry(int state)
{
	if (state == GLUT_LEFT)
	{
		printf("Moust is outside of window..\a\n");
	}
	else if (state == GLUT_ENTERED)
	{
		printf("Moust is inside of window..\a\n");
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		printf("a is pressed.. %d, %d\a\n", x, y);
		break;
	case 'b':
		printf("b is pressed.. %d, %d\a\n", x, y);
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Mouse and Keyboard");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseProcess);
	// ���� ������ ���� ����ϸ� �ȵȴ�.
	
	// glutPassiveMotionFunc(mousePassiveMotion); 
	// �����϶����� ���콺 ��ǥ ǥ�� -> ���ϴ� ���� �׸��� �׸��� �ٵ� �����϶����� ����� �ٽ� �׸��°Ŷ� �׸��� ���� �ʰ� ���� ���콺�� ��ġ�� �׷����� �������� ��������.
	// �����϶����� history�� �����س��� �����϶����� for������ ������ ���� �� ������ �� -> �׸� �׸��� ����
	
	// glutMotionFunc(mouseAvtiveMotion);
	// glutEntryFunc(mouseEntry);
	glutMainLoop();
	return 0;
}

// ���� �׸��� �׸��� ������ glutReDisplayFunc(display); ���