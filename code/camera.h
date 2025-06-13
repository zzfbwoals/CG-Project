// 20214045_류재민_FinalProject
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
    void initCamera(int index); // 추가: 초기 카메라 설정 함수

    extern Camera cameras[4];
    extern int viewport;

#ifdef __cplusplus
}
#endif