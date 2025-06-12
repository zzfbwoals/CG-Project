#pragma warning(disable:4996)

#include "camera.h"
#include <math.h>
#include <GL/glut.h>

Camera cameras[4] = {
    {0.0, 0.0, 50.0, 0.0, 1.0, 0.0, 90.0, 0.0, 50.0},    // 앞
    {35.0, 25.0, 35.0, 0.0, 1.0, 0.0, 65.0, 45.0, 50.0}, // 무작위
    {0.0, 50.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 50.0},    // 위
    {50.0, 0.0, 0.0, 0.0, 1.0, 0.0, 90.0, 90.0, 50.0}    // 옆
};

int selected_viewport = -1;

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
