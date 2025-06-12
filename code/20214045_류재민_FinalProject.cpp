#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include "model.h"
#include "camera.h"

// 조명 설정
GLfloat lightPosition[4] = { 0.0, 0.0, -1.0, 1.0 }; // 앞쪽에서 조명
GLfloat ambientLight[4] = { 0.2, 0.2, 0.2, 1.0 };   // 약한 주변광
GLfloat diffuseLight[4] = { 0.4, 0.4, 0.4, 1.0 };   // 약한 산란광
GLfloat specular[4] = { 0.3, 0.3, 0.3, 1.0 };       // 약한 반사광

// 뷰포트 위치 배열
int viewport_pos[16] = {
    0, 0, 400, 400,     // 0: 앞
    400, 0, 400, 400,   // 1: 무작위
    0, 400, 400, 400,   // 2: 위
    400, 400, 400, 400  // 3: 옆
};

void drawLine();
void drawRect();

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    /*
    뷰 포트
    2 3
    0 1
    */

    // 각 뷰포트에 대해 카메라 설정 적용
    for (int i = 0; i < 4; i++) {
        glPushMatrix();

        glViewport(viewport_pos[i * 4], viewport_pos[i * 4 + 1], viewport_pos[i * 4 + 2], viewport_pos[i * 4 + 3]);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-50, 50, -50, 50, -50.0, 500.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // 카메라 시점 설정
        gluLookAt(cameras[i].eyeX, cameras[i].eyeY, cameras[i].eyeZ,
            0.0, 0.0, 0.0,
            cameras[i].upX, cameras[i].upY, cameras[i].upZ);

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

// 방향키 입력 처리
void specialKeys(int key, int x, int y) {
    if (selected_viewport == -1) return; // 뷰포트가 선택되지 않았으면 아무 동작 안 함

    Camera* cam = &cameras[selected_viewport];
    if (key == GLUT_KEY_UP) {
        cam->theta -= 5.0; // 위로 이동
    }
    if (key == GLUT_KEY_DOWN) {
        cam->theta += 5.0; // 아래로 이동
    }
    if (key == GLUT_KEY_LEFT) {
        cam->phi -= 5.0; // 왼쪽으로 이동
    }
    if (key == GLUT_KEY_RIGHT) {
        cam->phi += 5.0; // 오른쪽으로 이동
    }

    // theta와 phi의 범위 제한
    if (cam->theta > 360.0) cam->theta = fmod((double)cam->theta, 360.0);
    if (cam->phi > 360.0) cam->phi = fmod((double)cam->phi, 360.0);

    eyePosition(selected_viewport);
}

// 일반 키 입력 처리
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        selected_viewport = 2; // 위
        break;
    case '2':
        selected_viewport = 3; // 옆
        break;
    case '3':
        selected_viewport = 0; // 앞
        break;
    case '4':
        selected_viewport = 1; // 무작위
        break;
    }
    glutPostRedisplay();
}

void drawRect() {
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.5f, 0.0f);

    glBegin(GL_QUADS);
    glVertex3f(-25.0f, -21.0f, -45.0f);
    glVertex3f(25.0f, -21.0f, -45.0f);
    glVertex3f(25.0f, -21.0f, 40.0f);
    glVertex3f(-25.0f, -21.0f, 40.0f);
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
    glutSpecialFunc(specialKeys); 
    glutKeyboardFunc(keyboard);  
    glutMainLoop();

    for (int i = 0; i < global_model1.vNum; i++)
        free(global_model1.vPoint[i]);
    free(global_model1.vPoint);

    for (int i = 0; i < global_model1.fNum; i++)
        free(global_model1.fPoint[i]);
    free(global_model1.fPoint);
    return 0;
}