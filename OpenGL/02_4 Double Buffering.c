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

	// 중요
	glPushMatrix(); // 스택 ex)자동차 바퀴 같은거에 사용 똑같은거 여러개 일 때
	//              x축  y축  z축
	glRotatef(spin, 0.0, 0.0, 1.0); // 중요 spin 이라는 값을 가지고 회전시키라는 것, 원점을 기준으로 돈다 (지금 코드의 경우 0, 0 이 원점)
	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
	glRectf(-25.0, -25.0, 25.0, 25.0); // 사각형 그리기 durld
	glPopMatrix(); // 스택

	glutSwapBuffers(); // 더블 버퍼링 사용 시 flush() 대신에 이걸 사용해야함 중요!
}

void spinDisplay(void)
{
	spin = spin + 0.5; // 0.5 도 씩 회전
	if (spin > 360.0)spin = spin - 360.0; // 360도 다 돌아가면 다시 0으로 세팅
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // 윈도우 배경을 검은색으로 설정
	glShadeModel(GL_FLAT); // Flat Shading으로 설정
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 더블 버퍼링으로 선언
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("02_4 사각형 회전");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}