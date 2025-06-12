#pragma once
#include <math.h>
#include <GL/glut.h>

typedef struct {
    GLfloat eyeX, eyeY, eyeZ;
    GLfloat upX, upY, upZ;
    GLfloat theta, phi, r;
} Camera;

#ifdef __cplusplus
extern "C" {
#endif

    void eyePosition(int index);

    extern Camera cameras[4];
    extern int viewport;

#ifdef __cplusplus
}
#endif
