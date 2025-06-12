#pragma warning(disable:4996)

#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

Model ObjLoad(const char* name) 
{
    Model model = { 0 };
    char line[256];
    FILE* fp = fopen(name, "r");
    if (!fp) 
    {
        printf("파일 열기 실패: %s\n", name);
        exit(1);
    }

    // 1차 패스: 개수 세기
    while (fgets(line, sizeof(line), fp)) 
    {
        if (strncmp(line, "v ", 2) == 0) model.vNum++;
        else if (strncmp(line, "f ", 2) == 0) model.fNum++;
    }
    rewind(fp);

    // 메모리 할당
    model.vPoint = (double**)malloc(sizeof(double*) * model.vNum);
    for (int i = 0; i < model.vNum; i++)
        model.vPoint[i] = (double*)malloc(sizeof(double) * 3);

    model.fPoint = (int**)malloc(sizeof(int*) * model.fNum);
    for (int i = 0; i < model.fNum; i++)
        model.fPoint[i] = (int*)malloc(sizeof(int) * 3);

    int vCount = 0, fCount = 0;
    while (fgets(line, sizeof(line), fp)) 
    {
        if (strncmp(line, "v ", 2) == 0) 
        {
            sscanf(line, "v %lf %lf %lf", &model.vPoint[vCount][0], &model.vPoint[vCount][1], &model.vPoint[vCount][2]);
            vCount++;
        }
        else if (strncmp(line, "f ", 2) == 0) 
        {
            char v1[32], v2[32], v3[32];
            sscanf(line, "f %s %s %s", v1, v2, v3);
            sscanf(v1, "%d", &model.fPoint[fCount][0]);
            sscanf(v2, "%d", &model.fPoint[fCount][1]);
            sscanf(v3, "%d", &model.fPoint[fCount][2]);
            model.fPoint[fCount][0]--;
            model.fPoint[fCount][1]--;
            model.fPoint[fCount][2]--;
            fCount++;
        }
    }
    fclose(fp);
    printf("MODEL 로드 성공: %d 정점, %d 면\n", model.vNum, model.fNum);
    return model;
}

void rendering(Model model) 
{
    glPointSize(5);
    glColor3f(0.9, 0.0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < model.vNum; i++)
        glVertex3f(model.vPoint[i][0], model.vPoint[i][1], model.vPoint[i][2]);
    glEnd();

    glColor3f(0.5, 0.5, 0.5);
    for (int i = 0; i < model.fNum; i++) 
    {
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++)
            glVertex3f(model.vPoint[model.fPoint[i][j]][0], model.vPoint[model.fPoint[i][j]][1], model.vPoint[model.fPoint[i][j]][2]);
        glEnd();
    }

    glLineWidth(2);
    glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < model.fNum; i++) 
    {
        glBegin(GL_LINES);
        for (int j = 0; j < 3; j++) 
        {
            int next = (j + 1) % 3;
            glVertex3f(model.vPoint[model.fPoint[i][j]][0], model.vPoint[model.fPoint[i][j]][1], model.vPoint[model.fPoint[i][j]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][next]][0], model.vPoint[model.fPoint[i][next]][1], model.vPoint[model.fPoint[i][next]][2]);
        }
        glEnd();
    }
}

void drawModel(Model model)
{
    glTranslatef(0.0f, -20.0f, -10.0f);
    glScalef(0.7f, 0.7f, 0.7f);
	rendering(model);
}
