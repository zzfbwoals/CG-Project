#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0.0f, 0.0f, 0.0f);
	glFlush();
}

// 메뉴를 선택했을 때 수행되는 함수
void main_menu_select(int value)
{
	switch (value) {
	case 1:
		glutSetWindowTitle("Menu 1");
		printf("Menu 1 selected\n");
		break;
	case 2:
		glutSetWindowTitle("Menu 2");
		printf("Menu 2 selected\n");
		break;
	case 3:
		glutSetWindowTitle("Menu 3");
		printf("Menu 3 selected\n");
		break;
	case 666:
		glutSetWindowTitle("Exit");
		printf("Exit selected\n");
		exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Pop-up Menu Example");
	glutDisplayFunc(display);
	// 메뉴 생성
	glutCreateMenu(main_menu_select);
	glutAddMenuEntry("Menu 1", 1);
	glutAddMenuEntry("Menu 2", 2);
	glutAddMenuEntry("Menu 3", 3);
	glutAddMenuEntry("Exit", 666);
	// 메뉴를 마우스 오른쪽 버튼에 연결
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}