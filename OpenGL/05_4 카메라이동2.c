#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // 행렬 초기화

	gluLookAt(0.0, 0.0, 5.0,    // 카메라 위치 (0, 0, 2)
		0.0, 0.0, 0.0,    // 대상 지점 (0, 0, 0)
		0.0, 1.0, 0.0);   // up 벡터 (0, 1, 0) 정확히 이해해야함.
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0); // x축으로 90도 회전

	glutWireTeapot(1.0); // 차를 그린다.

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // 행렬 초기화
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // 원근 투영 변환
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformation Teapot");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}