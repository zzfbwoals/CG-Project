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

// 윈도우 창 안에서만 눌려야 함.
void mouseProcess(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Left mouse button if pressed..\a\n"); // \a 는 소리나는 역할
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
	// 밑의 세개는 같이 사용하면 안된다.
	
	// glutPassiveMotionFunc(mousePassiveMotion); 
	// 움직일때마다 마우스 좌표 표시 -> 원하는 곳에 그림을 그릴때 근데 움직일때마다 지우고 다시 그리는거라 그린게 남지 않고 현재 마우스의 위치만 그려지고 전에꺼는 지워진다.
	// 움직일때마다 history를 저장해놓고 움직일때마다 for문에서 뒤져서 점을 다 찍어줘야 함 -> 그림 그리는 원리
	
	// glutMotionFunc(mouseAvtiveMotion);
	// glutEntryFunc(mouseEntry);
	glutMainLoop();
	return 0;
}

// 뭔가 그림을 그리고 싶을때 glutReDisplayFunc(display); 사용