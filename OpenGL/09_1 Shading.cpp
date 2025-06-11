#include <stdlib.h>
#include <GL/glut.h>

void init(void)
{
	// Material Property
	GLfloat mat_ambient[] = { 0.329412, 0.223529, 0.027451 };
	GLfloat mat_diffuse[] = { 0.780392, 0.568627, 0.113725 };
	GLfloat mat_specular[] = { 0.992157, 0.941176, 0.807843 };
	GLfloat mat_shininess[] = { 0.21794872 * 128 };

	// Lighting Property
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glutSolidTeapot(1.0);
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main_menu_select(int value)
{
	switch (value)
	{
	case 1:
		glShadeModel(GL_FLAT);
		glutPostRedisplay();
		break;
	case 2:
		glShadeModel(GL_SMOOTH);
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("09_1 Shading");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// pop up 메뉴를 생성하고 세부메뉴의 이름과 메뉴의 번호를 할당
	glutCreateMenu(main_menu_select);
	glutAddMenuEntry("Flat Shading", 1);
	glutAddMenuEntry("Smooth Shading", 2);

	// 마우스의 오른쪽 버튼에 메뉴를 연결합니다.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}