#include <stdlib.h>
#include <GL/glut.h>

void init(void)
{

	// Lighting Property
	GLfloat light_position[] = { 1.0, 2.0, 3.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 1.0, 0.0, 1.0 };	// 주변 반사광은 녹색
	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };	// 확산 반사광은 빨간색
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };	// 반사광은 백색

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);	// 부드러운 음영

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	// 조명 위치
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	// 주변 반사광
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	// 확산 반사광
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	// 반사광

	glEnable(GL_LIGHTING);	// 조명 사용
	glEnable(GL_LIGHT0);	// 조명 0번 사용
	glEnable(GL_DEPTH_TEST);	// 깊이 테스트 사용
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 화면 지우기
	glutSolidTeapot(0.5);	// 찻주전자 그리기
	glFlush();	// 그리기
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	// 뷰포트 설정
	glMatrixMode(GL_PROJECTION);	// 투영 행렬 모드 설정
	glLoadIdentity();	// 단위 행렬로 초기화

	if(w<=h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);	// 직교 투영
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);	// 직교 투영
	glMatrixMode(GL_MODELVIEW);	// 모델 뷰 행렬 모드 설정
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// GLUT 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	// 단일 버퍼, RGB 모드, 깊이 버퍼 사용
	glutInitWindowSize(500, 500);	// 윈도우 크기 설정
	glutInitWindowPosition(100, 100);	// 윈도우 위치 설정
	glutCreateWindow("Lighting");	// 윈도우 생성
	init();	// 초기화 함수 호출

	glutDisplayFunc(display);	// 디스플레이 콜백 함수 등록
	glutReshapeFunc(reshape);	// 리쉐이프 콜백 함수 등록
	glutMainLoop();	// 이벤트 루프 진입
	return 0;
}