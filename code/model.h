#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
	void calcNormal(double* v0, double* v1, double* v2, double* normal);
    void rendering(Model model);

    extern Model model;
    extern GLfloat modelColor[3];
    extern int light;

#ifdef __cplusplus
}
#endif
