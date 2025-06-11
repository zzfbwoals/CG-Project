#include <stdlib.h>
#include <time.h>
#include <gl/glut.h>

#define WIDTH 800
#define HEIGHT 600
#define AXIS_SIZE 60
#define TIMER 100

void SetupRC();
void RenderScene(void);
void ChangeSize(int w, int h);
void TimerFunction(int value);
void MenuFunc(int button);

float yRot = 0.0f; // Y축 회전 각도

int menu_main;
int menu_depth_test;
int menu_cull_test;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Hidden Surface");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutTimerFunc(TIMER, TimerFunction, 1);

	// 팝업 메뉴
	menu_depth_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("은면제거 on", 1);
	glutAddMenuEntry("은면제거 off", 2);
	menu_cull_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("컬링 on", 3);
	glutAddMenuEntry("컬링 off", 4);
	menu_main = glutCreateMenu(MenuFunc);
	glutAddSubMenu("은면제거", menu_depth_test);
	glutAddSubMenu("컬링", menu_cull_test);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// 팝업 메뉴 끝

	SetupRC();
	glutMainLoop();
	
	return 0;
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glLoadIdentity();
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	{
		// 앞면
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);

		// 왼쪽면
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		// 뒷면
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		// 뒷면 안쪽면: 정점의 방향 유의
		// 정점 순서를 달리해서 법선벡터 앞뒤
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
	glFrontFace(GL_CCW); // 정점의 방향을 시계 방향으로 설정
	glEnable(GL_CULL_FACE); // 컬링 활성화
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 배경색 설정
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	// 원근 투영 사용
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60.0f, fAspect, 1.0f, 500.0);
	glTranslatef(0.0f, 0.0f, -300.0f); // 카메라 위치 설정
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // 카메라 회전 설정
	// glRotatef(45.0f, 0.0f, 1.0f, 0.0f); // 카메라 회전 설정

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	yRot += 1.0f;

	glutPostRedisplay(); // 화면 갱신
	glutTimerFunc(TIMER, TimerFunction, 1); // 타이머 함수 재설정
}

void MenuFunc(int button)
{
	switch (button) {
	case 1: // 은면제거 on
		glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
		break;
	case 2: // 은면제거 off
		glDisable(GL_DEPTH_TEST); // 깊이 테스트 비활성화
		break;
	case 3: // 컬링 on
		glEnable(GL_CULL_FACE); // 컬링 활성화
		break;
	case 4: // 컬링 off
		glDisable(GL_CULL_FACE); // 컬링 비활성화
		break;
	default:
		break;
	}
	glutPostRedisplay(); // 화면 갱신
}