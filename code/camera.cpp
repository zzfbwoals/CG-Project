// 20214045_�����_FinalProject
#pragma warning(disable:4996)
#include "camera.h"

// gluLookAt �Լ��� �ʿ��� ī�޶� ����ü
Camera cameras[4] = {
    {0.0, 0.0, 50.0, 0.0, 1.0, 0.0, 90.0, 0.0, 50.0},    // ��
    {35.0, 25.0, 35.0, 0.0, 1.0, 0.0, 65.0, 45.0, 50.0}, // ������
    {0.0, 50.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 50.0},    // ��
    {50.0, 0.0, 0.0, 0.0, 1.0, 0.0, 90.0, 90.0, 50.0}    // ��
};

void initCamera(int index) {
    switch (index) {
    case 0: // ��
        cameras[index] = { 0.0, 0.0, 50.0, 0.0, 1.0, 0.0, 90.0, 0.0, 50.0 };
        break;
    case 1: // ������
        cameras[index] = { 35.0, 25.0, 35.0, 0.0, 1.0, 0.0, 65.0, 45.0, 50.0 };
        break;
    case 2: // ��
        cameras[index] = { 0.0, 50.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 50.0 };
        break;
    case 3: // ��
        cameras[index] = { 50.0, 0.0, 0.0, 0.0, 1.0, 0.0, 90.0, 90.0, 50.0 };
        break;
    }
    eyePosition(index); // �ʱ� ��ġ�� ī�޶� ����
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