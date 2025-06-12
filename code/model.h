#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

typedef struct {
    double** vPoint;
    int** fPoint;
    int vNum;
    int fNum;
} Model;

#ifdef __cplusplus
extern "C" {
#endif

    Model ObjLoad(const char* name);
    void rendering(Model model);
    void drawModel(Model model);

    extern Model model;
    extern GLfloat modelColor[3];

#ifdef __cplusplus
}
#endif
