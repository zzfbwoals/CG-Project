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
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 0.0); // 빨강색
	glutWireCube(1.0);

	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);; // 녹색
	glTranslatef(-1.5, 0.0, 1.5); // 물체의 이동에 따른 변화 학인
	glutWireCube(1.0);

	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0); // 파랑색
	glTranslatef(1.5, 0.0, 1.5); // 물체의 이동에 따른 변화 확인
	glutWireCube(1.0);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // 행렬 초기화
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // 원근 투영 확인
	//glOrtho(-7.0, 7.0, -7.0, 7.0, 1.5, 20.0); // 병렬 투영 확인
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("투영 방법 예제");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}