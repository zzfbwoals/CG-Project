// 20214045_류재민_FinalProject
#pragma warning(disable:4996)

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

Model global_model1;

GLfloat lightPosition[4] = { 1.0, 2.0, 0.0, 1.0 };
GLfloat ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseLight[4] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[4] = { 1, 1, 1, 1 };

void rendering(Model model) {
    glPointSize(5);
    glColor3f(0.9, 0.0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < model.vNum; i++)
        glVertex3f(model.vPoint[i][0], model.vPoint[i][1], model.vPoint[i][2]);
    glEnd();

    glColor3f(0.5, 0.5, 0.5);
    for (int i = 0; i < model.fNum; i++) {
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++)
            glVertex3f(model.vPoint[model.fPoint[i][j]][0], model.vPoint[model.fPoint[i][j]][1], model.vPoint[model.fPoint[i][j]][2]);
        glEnd();
    }

    glLineWidth(2);
    glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < model.fNum; i++) {
        glBegin(GL_LINES);
        for (int j = 0; j < 3; j++) {
            int next = (j + 1) % 3;
            glVertex3f(model.vPoint[model.fPoint[i][j]][0], model.vPoint[model.fPoint[i][j]][1], model.vPoint[model.fPoint[i][j]][2]);
            glVertex3f(model.vPoint[model.fPoint[i][next]][0], model.vPoint[model.fPoint[i][next]][1], model.vPoint[model.fPoint[i][next]][2]);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // glRotatef(90.0, 0.0, 1.0, 0.0); // 카메리의 위치를 x축을 기준으로 90도 회전

    glPushMatrix();
    // 모델 위치 내리기 (Y축 아래로)
    glTranslatef(0.0f, -25.0f, 0.0f);  // 모델을 아래로 내림 (스케일 기준 값)
    rendering(global_model1);
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

Model ObjLoad(const char* name) {
    Model model = { 0 };
    char line[256];
    FILE* fp = fopen(name, "r");
    if (!fp) {
        printf("파일 열기 실패: %s\n", name);
        exit(1);
    }

    // 1차 패스: 개수 세기
    while (fgets(line, sizeof(line), fp)) {
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
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "v ", 2) == 0) {
            sscanf(line, "v %lf %lf %lf", &model.vPoint[vCount][0], &model.vPoint[vCount][1], &model.vPoint[vCount][2]);
            vCount++;
        }
        else if (strncmp(line, "f ", 2) == 0) {
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

void init() {
    global_model1 = ObjLoad("dino.obj");

    glClearColor(1.0, 1.0, 1.0, 0.0);
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