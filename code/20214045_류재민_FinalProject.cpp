// 20214045_류재민_FinalProject
#pragma warning(disable:4996)

#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

Model global_model1;

GLfloat lightPosition[4] = { 1.0, 2.0, 0.0, 1.0 };
GLfloat ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseLight[4] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[4] = { 1, 1, 1, 1 };

void drawRect();

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0); // 카메리의 위치를 x축을 기준으로 90도 회전

    drawRect();

    glPushMatrix();
    // 모델 위치 내리기 (Y축 아래로)
    glTranslatef(0.0f, -25.0f, -10.0f);  // 모델을 아래로 내림 (스케일 기준 값)
	glScalef(0.7f, 0.7f, 0.7f); // 모델 크기 조정
    rendering(global_model1);
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void init() {
    global_model1 = ObjLoad("dino.obj");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawRect() {
    glDisable(GL_LIGHTING);  // 조명 비활성화 (단색 표현)
    glColor3f(0.0f, 0.1f, 0.0f);  // 밝은 회색 바닥

    // 사각형 그리기
    glBegin(GL_QUADS);
    glVertex3f(-25.0f, -25.01f, -45.0f);
    glVertex3f(25.0f, -25.01f, -45.0f);
    glVertex3f(25.0f, -25.01f, 40.0f);
    glVertex3f(-25.0f, -25.01f, 40.0f);
    glEnd();

    glEnable(GL_LIGHTING);  // 조명 다시 켜기
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OBJ VIEWER");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    for (int i = 0; i < global_model1.vNum; i++)
        free(global_model1.vPoint[i]);
    free(global_model1.vPoint);

    for (int i = 0; i < global_model1.fNum; i++)
        free(global_model1.fPoint[i]);
    free(global_model1.fPoint);
    return 0;
}