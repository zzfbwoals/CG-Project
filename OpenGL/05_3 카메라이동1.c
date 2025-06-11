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

	// Viewing Transformation
	// 5를 수정하면 거리가 멀어져서 작게 보임. glFrustum()사용해서 가능.
	gluLookAt(0.0, 0.0, 5.0,    // 카메라 위치 (0, 0, 2)
		0.0, 0.0, 0.0,    // 대상 지점 (0, 0, 0)
		0.0, 1.0, 0.0);   // up 벡터 (0, 1, 0) 정확히 이해해야함.

	//glRotatef(90.0, 1.0, 0.0, 0.0); // 카메리의 위치를 x축을 기준으로 90도 회전
	//glTranslatef(0.0, 0.0, -2.0); // z축으로 -2.0만큼 이동. (물체가 작아짐)
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