#include <stdio.h>
#include <GL/glut.h>

GLfloat position[] = { 0.0, 4.5, 0.0, 1.0 }; // 조명 위치 변경 변수

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // 배경색 설정
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; // 주변광
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // 확산광
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // 반사광

	glShadeModel(GL_SMOOTH); // 음영 모델 설정
	glEnable(GL_LIGHTING); // 조명 활성화
	glEnable(GL_LIGHT0); // 조명 0 활성화
	glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); // 주변광 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // 확산광 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // 반사광 설정

	// 감쇠율
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.004);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 화면 지우기
	
	// 조명 이동 적용
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, position); // 조명 위치 설정

	// 조명의 위치를 Cube로 출력
	glTranslated(position[0], position[1], position[2]);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.5);

	glEnable(GL_LIGHTING);
	glPopMatrix();

	glutSolidSphere(1, 50, 50);
	glFlush(); // 화면에 그리기
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w, 5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			position[1] -= 0.1;
			printf("Light Position: (%.2lf, %.2lf, %.2lf)\n", position[0], position[1], position[2]);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			position[1] += 0.1;
			printf("Light Position: (%.2lf, %.2lf, %.2lf)\n", position[0], position[1], position[2]);
		}
		break;
	defalut:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Moving Lighting Example"); // 윈도우 생성
	init();
	glutDisplayFunc(display); // 디스플레이 콜백 함수 등록
	glutReshapeFunc(reshape); // 리쉐이프 콜백 함수 등록
	glutMouseFunc(mouse); // 마우스 콜백 함수 등록
	glutMainLoop(); // 이벤트 루프 시작
	return 0;
}