#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>

// 정육먼체의 정점 좌표 지정
GLfloat MyVertices[8][3] = {
	{-0.25, -0.25, 0.25},
	{-0.25, 0.25, 0.25},
	{0.25, 0.25, 0.25},
	{0.25, -0.25, 0.25},
	{-0.25, -0.25, -0.25},
	{-0.25, 0.25, -0.25},
	{0.25, 0.25, -0.25},
	{0.25, -0.25, -0.25}
};

// 정육면체의 정점의 색 지정
GLfloat MyColors[8][3] = {
	{0.2, 0.2, 0.2},
	{1.0, 0.0, 0.0},
	{1.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{1.0, 0.0, 1.0},
	{1.0, 1.0, 1.0},
	{0.0, 1.0, 1.0}
};

// 정 육면체의 여섯 면에 대한 정점 정보 리스트
GLubyte MyVertexList[24] = {
	0,3,2,1,
	2,3,7,6,
	0,4,7,3,
	1,2,6,5,
	4,5,6,7,
	0,1,5,4
};

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(30.0, 1.0, 1.0, 1.0);
	for (GLint i = 0; i < 6; i++)
	{
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[i * 4]);
	}
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("RGB Color Cube");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}