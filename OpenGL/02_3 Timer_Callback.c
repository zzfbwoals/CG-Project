#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <time.h>

// 색상 설정
unsigned char PALETTE[16][3] = {
	{255, 255, 255},		// WHITE
	{0, 255, 255},			// CYAN
	{255, 0, 255},			// PUPPLE
	{0, 0, 255},			// BLUE
	{192, 192, 192},		// LIGHT GRAY
	{128, 128, 128},		// DARK GRAY
	{0, 128, 128},			// DARK TEAL
	{128, 0, 128},			// DARK PUPPLE
	{0, 0, 128},			// DARK BLUE
	{255, 255, 0},			// YELLOW
	{0, 255, 0},			// GREEN
	{128, 128, 0},			// DARK YELLOW
	{0, 128, 0},			// DARK GREEN
	{255, 0, 0},			// RED
	{128, 0, 0},			// DARK RED
	{0, 0, 0}				// BLACK
};

GLfloat Delta = 0.0;
GLint Index = 0;
GLfloat Red = 0.0;
GLfloat Green = 0.0;
GLfloat Blue = 0.0;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 3D Ortho
}

void MyDisplay()
{
	Red = PALETTE[Index][0] / 255.0f; // 0~1 값 구하려고 나눔
	Green = PALETTE[Index][1] / 255.0f;
	Blue = PALETTE[Index][2] / 255.0f;
	glColor3f(Red, Green, Blue);

	// 회전이 아닌 두 개의 X 자 선을 계속 그려나가는 것
	glBegin(GL_LINES);
	glVertex3f(-1.0 + Delta, 1.0, 0.0);
	glVertex3f(1.0 - Delta, -1.0, 0.0);
	glVertex3f(-1.0, -1.0 + Delta, 0.0);
	glVertex3f(1.0, 1.0 - Delta, 0.0);
	glEnd();
	glFlush();
	// glutSwapBuffers(); 더블 버퍼링 함수
}

void MyTimer(int Value)
{
	if (Delta < 2.0f) Delta = Delta + 0.01;
	else
	{
		Delta = 0.0;
		Index++;
		if (Index > 15)
		{
			Index = 0; // 색 인덱스를 다시 처음으로 초기화
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // SINGLE 이 디폴트 DOUBLE 사용시 깜빡거림현상 해결가능
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Timer Callback 예제");
	init();
	glutTimerFunc(10, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}