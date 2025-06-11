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

float yRot = 0.0f; // Y�� ȸ�� ����

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

	// �˾� �޴�
	menu_depth_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("�������� on", 1);
	glutAddMenuEntry("�������� off", 2);
	menu_cull_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("�ø� on", 3);
	glutAddMenuEntry("�ø� off", 4);
	menu_main = glutCreateMenu(MenuFunc);
	glutAddSubMenu("��������", menu_depth_test);
	glutAddSubMenu("�ø�", menu_cull_test);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// �˾� �޴� ��

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
		// �ո�
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);

		// ���ʸ�
		glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		// �޸�
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		// �޸� ���ʸ�: ������ ���� ����
		// ���� ������ �޸��ؼ� �������� �յ�
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
	glEnable(GL_DEPTH_TEST); // ���� �׽�Ʈ Ȱ��ȭ
	glFrontFace(GL_CCW); // ������ ������ �ð� �������� ����
	glEnable(GL_CULL_FACE); // �ø� Ȱ��ȭ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ���� ����
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	// �������� ���� ���� ����
	glViewport(0, 0, w, h);

	// ���� ���� ���
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60.0f, fAspect, 1.0f, 500.0);
	glTranslatef(0.0f, 0.0f, -300.0f); // ī�޶� ��ġ ����
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // ī�޶� ȸ�� ����
	// glRotatef(45.0f, 0.0f, 1.0f, 0.0f); // ī�޶� ȸ�� ����

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	yRot += 1.0f;

	glutPostRedisplay(); // ȭ�� ����
	glutTimerFunc(TIMER, TimerFunction, 1); // Ÿ�̸� �Լ� �缳��
}

void MenuFunc(int button)
{
	switch (button) {
	case 1: // �������� on
		glEnable(GL_DEPTH_TEST); // ���� �׽�Ʈ Ȱ��ȭ
		break;
	case 2: // �������� off
		glDisable(GL_DEPTH_TEST); // ���� �׽�Ʈ ��Ȱ��ȭ
		break;
	case 3: // �ø� on
		glEnable(GL_CULL_FACE); // �ø� Ȱ��ȭ
		break;
	case 4: // �ø� off
		glDisable(GL_CULL_FACE); // �ø� ��Ȱ��ȭ
		break;
	default:
		break;
	}
	glutPostRedisplay(); // ȭ�� ����
}