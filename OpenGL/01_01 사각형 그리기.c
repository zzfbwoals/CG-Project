#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void display(void) 
{
	glColor3f(1.0, 1.0, 1.0); // 흰색으로 설정

	// 사각형의 좌표 입력
	glBegin(GL_POLYGON);
		// 점 4개 좌표 (사각형) xyz
		glVertex3f(0.25, 0.25, 0.0); // 투영 박스가 0~1 의 크기여서 0.25 0.75의 좌표를 준 것임. gl->지엘함수 3->파라미터수 f->부동소수
		glVertex3f(0.75, 0.25, 0.0); 
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glFlush(); // 사각형을 화면에 그림
	printf("glutDisplayFunc(display)\n");
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // 윈도우 배경을 검은색으로 설정 (0~1)
	glClear(GL_COLOR_BUFFER_BIT); // 색상 버퍼를 지움
	glMatrixMode(GL_PROJECTION); // 이후의 행렬들을 Projection 행렬 스택에 적용
	glLoadIdentity(); // 단위 행렬(대각선만 1인 행렬)로 초기화

	// 직교 투영: left, right, bottom, top, near, far
	// 중요합니다**************
	// 투영박스 밖에 그림 그리면 안나옴
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) // argc, argv 매개변수: 실행을 할 때 명령을 받아서 그 명령을 쓸 수 있다 <- 뭔소리여... 집가서 이해
{
	glutInit(&argc, argv); // GLUT 상태를 초기화, 다른 glut 함수들 보다 항상 맨 먼저
	// 디스플레이 모드형식 선택: Single buffer & RGBA color 모드 선택, 3개 버퍼 모드중 하나 3개 색상 모드중 하나 사용
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// 창의 크기와 위치 설정
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("01 사각형 그리기"); // 윈도우생성, ID가 정수형으로 리턴된다.
	init();

	// 필요한 콜백함수 등록
	// 창을 축소확대 이동 등 할때마다 계속 함수가 콜백 된다.
	glutDisplayFunc(display);
	glutMainLoop(); // 이벤트 처리 엔진 시작, 마지막에 항상 있어야 함

	return 0;
}