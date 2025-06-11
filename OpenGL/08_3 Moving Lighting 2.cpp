#include <GL/glut.h>

static int spin = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);

	// 조명 회전
	glPushMatrix();
	glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// 조명의 위치를 Cube로 출력
	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);	// Cube의 색 표현을 위해 조명 비활성화
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.1);

	glEnable(GL_LIGHTING);
	glPopMatrix();

	glutSolidTorus(0.275, 0.85, 8, 15);
	glPopMatrix();
	glFlush();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		spin = (spin + 30) % 360;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Moving Lighting Example");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}