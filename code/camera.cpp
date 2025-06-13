// 20214045_류재민_FinalProject
#pragma warning(disable:4996)
#include "camera.h"

// gluLookAt 함수에 필요한 카메라 구조체
Camera cameras[4] = {
    {0.0, 0.0, 50.0, 0.0, 1.0, 0.0, 90.0, 0.0, 50.0},    // 앞
    {35.0, 25.0, 35.0, 0.0, 1.0, 0.0, 65.0, 45.0, 50.0}, // 무작위
    {0.0, 50.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 50.0},    // 위
    {50.0, 0.0, 0.0, 0.0, 1.0, 0.0, 90.0, 90.0, 50.0}    // 옆
};

void initCamera(int index) {
    switch (index) {
    case 0: // 앞
        cameras[index] = { 0.0, 0.0, 50.0, 0.0, 1.0, 0.0, 90.0, 0.0, 50.0 };
        break;
    case 1: // 무작위
        cameras[index] = { 35.0, 25.0, 35.0, 0.0, 1.0, 0.0, 65.0, 45.0, 50.0 };
        break;
    case 2: // 위
        cameras[index] = { 0.0, 50.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 50.0 };
        break;
    case 3: // 옆
        cameras[index] = { 50.0, 0.0, 0.0, 0.0, 1.0, 0.0, 90.0, 90.0, 50.0 };
        break;
    }
    eyePosition(index); // 초기 위치로 카메라 설정
}

void eyePosition(int index) {
    Camera* cam = &cameras[index];
    GLfloat dt = 1.0;
    GLfloat eyeXtemp = cam->r * sin((cam->theta + 0.0174532 - dt) * 0.0174532) * sin(cam->phi * 0.0174532);
    GLfloat eyeYtemp = cam->r * cos((cam->theta + 0.0174532 - dt) * 0.0174532);
    GLfloat eyeZtemp = cam->r * sin((cam->theta + 0.0174532 - dt) * 0.0174532) * cos(cam->phi * 0.0174532);

    cam->eyeX = cam->r * sin(cam->theta * 0.0174532) * sin(cam->phi * 0.0174532);
    cam->eyeY = cam->r * cos(cam->theta * 0.0174532);
    cam->eyeZ = cam->r * sin(cam->theta * 0.0174532) * cos(cam->phi * 0.0174532);

    cam->upX = eyeXtemp - cam->eyeX;
    cam->upY = eyeYtemp - cam->eyeY;
    cam->upZ = eyeZtemp - cam->eyeZ;

    glutPostRedisplay();
}