#pragma warning(disable:4996)

#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

Model global_model1;

GLfloat lightPosition[4] = { 0.0, 0.0, -1.0, 1.0 }; // 앞쪽에서 조명
GLfloat ambientLight[4] = { 0.2, 0.2, 0.2, 1.0 };   // 약한 주변광
GLfloat diffuseLight[4] = { 0.4, 0.4, 0.4, 1.0 };   // 약한 산란광
GLfloat specular[4] = { 0.3, 0.3, 0.3, 1.0 };       // 약한 반사광
int viewport_pos[16] = {
    0, 0, 400, 400,     // 1: 옆
    400, 0, 400, 400,   // 2: 앞
    0, 400, 400, 400,   // 3: 무작위
    400, 400, 400, 400  // 4: 위
};

void drawLine();
void drawRect();

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    /*
    뷰 포트 위치
    3 4
    1 2
    */

	// 각 뷰 포트의 카메라 각도
    for (int i = 0; i < 4; i++) {
        glPushMatrix();

        glViewport(viewport_pos[i * 4], viewport_pos[i * 4 + 1], viewport_pos[i * 4 + 2], viewport_pos[i * 4 + 3]);
        
        glOrtho(-50, 50, -50, 50, 1.0, 500.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // 각 뷰포트에 맞는 카메라 시점 설정
        if (i == 0) { // 앞
            gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        }
        else if (i == 1) { // 무작위
            gluLookAt(35.0, 25.0, 35.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        }
        else if (i == 2) { // 위
            gluLookAt(0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
        }
        else if (i == 3) { // 옆
            gluLookAt(50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        }

        // 발판
        glPushMatrix();
        drawRect();
        glPopMatrix();

        // 모델
        drawModel(global_model1);

        glPopMatrix();
    }

    // 전체 창에 중앙 십자선 그리기
    drawLine();

    glutSwapBuffers();
}

void init() {
    global_model1 = ObjLoad("dino.obj");

    glClearColor(0.2, 0.2, 0.2, 0.0);
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
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.5f, 0.0f);

	// 모델을 -20.0f 높이로 배치하여 발판 위에 놓이도록 함
    glBegin(GL_QUADS);
    glVertex3f(-25.0f, -20.01f, -45.0f);
    glVertex3f(25.0f, -20.01f, -45.0f);
    glVertex3f(25.0f, -20.01f, 40.0f);
    glVertex3f(-25.0f, -20.01f, 40.0f);
    glEnd();

    glEnable(GL_LIGHTING);
}

void drawLine() {
    glDisable(GL_LIGHTING);
    glViewport(0, 0, 800, 800);
    glPushMatrix();
    gluLookAt(0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
    glLineWidth(1.0);
    glPopMatrix();
    glEnable(GL_LIGHTING);
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