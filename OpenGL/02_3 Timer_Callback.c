#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <time.h>

// ���� ����
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
	Red = PALETTE[Index][0] / 255.0f; // 0~1 �� ���Ϸ��� ����
	Green = PALETTE[Index][1] / 255.0f;
	Blue = PALETTE[Index][2] / 255.0f;
	glColor3f(Red, Green, Blue);

	// ȸ���� �ƴ� �� ���� X �� ���� ��� �׷������� ��
	glBegin(GL_LINES);
	glVertex3f(-1.0 + Delta, 1.0, 0.0);
	glVertex3f(1.0 - Delta, -1.0, 0.0);
	glVertex3f(-1.0, -1.0 + Delta, 0.0);
	glVertex3f(1.0, 1.0 - Delta, 0.0);
	glEnd();
	glFlush();
	// glutSwapBuffers(); ���� ���۸� �Լ�
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
			Index = 0; // �� �ε����� �ٽ� ó������ �ʱ�ȭ
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // SINGLE �� ����Ʈ DOUBLE ���� �����Ÿ����� �ذᰡ��
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Timer Callback ����");
	init();
	glutTimerFunc(10, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}