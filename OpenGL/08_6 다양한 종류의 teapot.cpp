#include <stdlib.h>
#include <GL/glut.h>

void material_selection(float ambr, float ambg, float ambb, float difr, float difg, float difb, float specr, float specg, float specb, float shine) {
	float material_amb[4] = { ambr, ambg, ambb, 1.0f };
	float material_dif[4] = { difr, difg, difb, 1.0f };
	float material_spec[4] = { specr, specg, specb, 1.0f };
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void init(void)
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	material_selection(0.0215, 0.1745, 0.0215, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6);
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

void menu_select(int value)
{
	switch(value) {
		case 1: // Gold
			material_selection(0.24725, 0.1995, 0.0745, 0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4);
			break;
		case 2: // Red
			material_selection(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6);
			break;
		case 3: // Bronze
			material_selection(0.2125, 0.1275, 0.054, 0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2);
			break;
		case 4: // Emerald
			material_selection(0.0215, 0.1745, 0.0215, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6);
			break;
		default:
			exit(1);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Teapot with Material Selection");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutCreateMenu(menu_select);
	glutAddMenuEntry("Gold", 1);
	glutAddMenuEntry("Rubby", 2);
	glutAddMenuEntry("Bronze", 3);
	glutAddMenuEntry("Emerald", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}