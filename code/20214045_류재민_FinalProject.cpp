#pragma warning(disable:4996)
#include <time.h>
#include "model.h"
#include "camera.h"
#include "lodepng.h"

// 모델
Model model;

// 조명 설정
GLfloat lightPosition[4] = { 20.0, 20.0, 30.0, 1.0 };
GLfloat ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseLight[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };

// 색상
GLfloat floorColor[3] = { 0.0, 0.2, 0.0 }; // 바닥 기본 색상
GLfloat modelColor[3] = { 0.4, 0.29, 0.0 }; // 모델 기본 색상

// 상태
int light = 1; // 조명 상태 (1: 켜짐, 0: 꺼짐)
int viewport = -1; // 뷰포트 선택 상태 (-1은 선택되지 않음)
int texture = 1; // 텍스처 상태 (0: 사용 안 함, 1: 사용)

// 뷰포트 위치 배열
int viewportPos[16] = {
    0, 0, 400, 400,     // 0: 앞
    400, 0, 400, 400,   // 1: 무작위
    0, 400, 400, 400,   // 2: 위
    400, 400, 400, 400  // 3: 옆
};

// 그리기
void drawLine();
void drawRect();

// 메뉴 콜백 함수
void menuCallback(int value) {
    switch (value) {
	case 0: // 바닥 색상 변경
        floorColor[0] = (float)rand() / RAND_MAX; floorColor[1] = (float)rand() / RAND_MAX; floorColor[2] = (float)rand() / RAND_MAX;    
        printf("바닥 색상 변경: RGB(%.2f, %.2f, %.2f)\n", floorColor[0], floorColor[1], floorColor[2]);  
        break;
	case 1: // 모델 색상 변경
        modelColor[0] = (float)rand() / RAND_MAX; modelColor[1] = (float)rand() / RAND_MAX; modelColor[2] = (float)rand() / RAND_MAX;
        printf("모델 색상 변경: RGB(%.2f, %.2f, %.2f)\n", modelColor[0], modelColor[1], modelColor[2]);
        break;
	case 2: // 조명 토글
        light = !light;
        if (light) {
            glEnable(GL_LIGHT0);
            printf("조명 On\n");
        }
        else {
            glDisable(GL_LIGHT0);
            printf("조명 Off\n");
        }
        break;
	case 3: // 조명 색상 변경
        ambientLight[0] = (float)rand() / RAND_MAX; ambientLight[1] = (float)rand() / RAND_MAX; ambientLight[2] = (float)rand() / RAND_MAX; // ambient
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        diffuseLight[0] = (float)rand() / RAND_MAX; diffuseLight[1] = (float)rand() / RAND_MAX; diffuseLight[2] = (float)rand() / RAND_MAX; // diffuse
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        specular[0] = (float)rand() / RAND_MAX; specular[1] = (float)rand() / RAND_MAX; specular[2] = (float)rand() / RAND_MAX; // specular
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        printf("조명 색상 변경\n");
        break;
	case 4: // 텍스처 토글
        // 텍스처 기능은 제외 (빈 동작)
        printf("Texture toggle not implemented\n");
        break;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    for (int i = 0; i < 4; i++) {
        glPushMatrix();

        glViewport(viewportPos[i * 4], viewportPos[i * 4 + 1], viewportPos[i * 4 + 2], viewportPos[i * 4 + 3]);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-50, 50, -50, 50, -50.0, 500.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(cameras[i].eyeX, cameras[i].eyeY, cameras[i].eyeZ,
            0.0, 0.0, 0.0,
            cameras[i].upX, cameras[i].upY, cameras[i].upZ);

        // 사각형 바닥 그리기
        glPushMatrix();
        drawRect();
        glPopMatrix();

		// 모델 그리기
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, modelColor);
        drawModel(model);

        glPopMatrix();
    }

    drawLine();

    glutSwapBuffers();
}

void init() {
    model = ObjLoad("dino.obj");

    glClearColor(0.2, 0.2, 0.2, 0.0);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0001);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 랜덤 시드 초기화
    srand(time(NULL));

    // 팝업 메뉴 생성
    glutCreateMenu(menuCallback);
    glutAddMenuEntry("바닥 색상 변경", 0);
    glutAddMenuEntry("모델 색상 변경", 1);
    glutAddMenuEntry("조명 On/Off", 2);
    glutAddMenuEntry("조명 색상 변경", 3);
    glutAddMenuEntry("텍스처 On/Off", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void specialKeys(int key, int x, int y) {
    if (viewport == -1) return;

    Camera* c = &cameras[viewport];
    if (key == GLUT_KEY_UP) {
        c->theta -= 5.0;
    }
    if (key == GLUT_KEY_DOWN) {
        c->theta += 5.0;
    }
    if (key == GLUT_KEY_LEFT) {
        c->phi -= 5.0;
    }
    if (key == GLUT_KEY_RIGHT) {
        c->phi += 5.0;
    }

    if (c->theta > 360.0) c->theta = fmod((double)c->theta, 360.0);
    if (c->phi > 360.0) c->phi = fmod((double)c->phi, 360.0);

    eyePosition(viewport);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        viewport = 2; // 위
        break;
    case '2':
        viewport = 3; // 옆
        break;
    case '3':
        viewport = 0; // 앞
        break;
    case '4':
        viewport = 1; // 무작위
        break;
    }
    glutPostRedisplay();
}

void drawRect() {
    glDisable(GL_LIGHTING);
    glColor3f(floorColor[0], floorColor[1], floorColor[2]); // 동적 바닥 색상

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

    for (int i = 0; i < model.vNum; i++)
        free(model.vPoint[i]);
    free(model.vPoint);

    for (int i = 0; i < model.fNum; i++)
        free(model.fPoint[i]);
    free(model.fPoint);
    return 0;
}