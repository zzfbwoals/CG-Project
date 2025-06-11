#include <stdlib.h>
#include <GL/glut.h>

void myinit(void)
{
	GLfloat ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat position[] = { 0.0,0.3,2.0,0.0 };
	GLfloat lmodel_abient[] = { 0.4,0.4,0.4,1.0 };
	GLfloat local_view[] = { 0.0 };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// LIGHT0 조명 관련 정보
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// 전역 주변광 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_abient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(0.0, 0.1, 0.1, 0.0);
}

void display(void)
{
	// 재질 관련 정보
	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.7,0.7,0.7,1.0 };
	GLfloat mat_ambient_color[] = { 0.8,0.8,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.1,0.5,0.8,1.0 };
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 첫번째 행
	// 재질에 diffuse만 있고 Ambient, Specular, Shininess가 없는 경우
	glPushMatrix();
	glTranslatef(-3.75, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 diffuse, Specular만 있고 Shiniess가 low이며 Ambient, Emission이 없는 경우
	glPushMatrix();
	glTranslatef(-1.25, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 diffuse, Specular만 있고 Shininess가 high이며 Ambient, Emission이 없는 경우
	glPushMatrix();
	glTranslatef(1.25, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 diffuse, Emission만 있고 Ambient, Specular, Shininess가 없는 경우
	glPushMatrix();
	glTranslatef(3.75, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 두번째 행
	// 재질에 Ambient, diffuse만 있고 Specular, Shininess, Emission가 없는 경우
	glPushMatrix();
	glTranslatef(-3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 Ambient, diffuse, Specular만 있고 Shininess가 low이며 Emission이 없는 경우
	glPushMatrix();
	glTranslatef(-1.25, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 Ambient, diffuse, Specular만 있고 Shininess가 high이며 Emission이 없는 경우
	glPushMatrix();
	glTranslatef(1.25, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 Ambient, diffuse, Emission만 있고 Specular, Shininess가 없는 경우
	glPushMatrix();
	glTranslatef(3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 세번째 행
	// 재질에 Colored Ambient, diffuse만 있고 Specular, Shininess, Emission가 없는 경우
	glPushMatrix();
	glTranslatef(-3.75, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 Colored Ambient, diffuse, Specular만 있고 Shininess가 low이며 Emission이 없는 경우
	glPushMatrix();
	glTranslatef(-1.25, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 Colored Ambient, diffuse, Specular만 있고 Shininess가 high이며 Emission이 없는 경우
	glPushMatrix();
	glTranslatef(1.25, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// 재질에 Colored Ambient, diffuse, Emission만 있고 Specular, Shininess가 없는 경우
	glPushMatrix();
	glTranslatef(3.75, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	glFlush();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= (h * 2))
		glOrtho(-6.0, 6.0, -3.0 * ((GLfloat)h * 2) / (GLfloat)w, 3.0 * ((GLfloat)h * 2) / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-6.0 * ((GLfloat)w * 2) / (GLfloat)h, 6.0 * ((GLfloat)w * 2) / (GLfloat)h, -3.0, 3.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char key, int x, int y)
{
	switch(key) {
	case 27: // ESC
		exit(0);
		break;
	default:
		return;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 300);
	glutCreateWindow("Material Property");
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}