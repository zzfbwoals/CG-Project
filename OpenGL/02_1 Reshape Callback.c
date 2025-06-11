#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH); // 지정하지 않은 부분의 색을 자연스럽게 칠해줌, 각 정점의 색을 부드럽게 혼합하여 렌더링 <=> flat
}

void triangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(5.0, 5.0); // x=5 y=5 위치에 빨간색 칠하기
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(25.0, 5.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(5.0, 25.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	triangle();
	glFlush();
}

// reshape 에 의해 윈도우를 가로로 쭉 늘리면 밑변이 늘린만큼 늘어나야되는데 원래 형태 유지 가능
// 윈도우 창을 크기 조절 막 해도 원래 형태 유지
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // 화면에 뿌릴 도화지, gluOrtho()랑 비교해서 이해해야함 *******************
	// 3ds max viewport(alt+w) 라고 생각
	// w, h 산수계산 궁금하면 집에서 해보기
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Without Reshape recalculation
	//gluOrtho2D(0.0, 30.0, 0.0, 30.0);
	// 위를 주석 없애고 밑에를 주석 처리 하면 비율에 맞춰 크기를 조정해주지 못함

	// 비율에 맞춰 크기를 조정해주는 부분 제일 중요**************************
	// With Reshape recalculation
	if (w <= h) // 높이가 너비보다 더 크거나 같은 경우
		// gluOrtho2D(left, right, bottom, top) 를 지정
		gluOrtho2D(0.0, 30.0, 0.0, 30.0 * (float)h / (float)w); // 크기 조정
	else // 너비가 높이보다 더 큰 경우
		gluOrtho2D(0.0, 30.0 * (float)w / (float)h, 0.0, 30.0); // 크기 조정
	
	glMatrixMode(GL_MODELVIEW); // 안써도 디폴트로 적용 됨
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]); // 윈도우 제목
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape); // Reshape callback function 등록
	glutMainLoop();
	return 0;
}