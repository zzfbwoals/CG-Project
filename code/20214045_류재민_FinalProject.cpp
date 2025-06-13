// 20214045_류재민_FinalProject
#pragma warning(disable:4996)
#include <time.h>
#include <iostream>
#include "model.h"
#include "camera.h"
#include "lodepng.h"

/*****************
     1번 문제
*****************/

// 기본 함수
void init();
void display();
void reshape(int w, int h);

// 모델
Model dino;
Model eye;
Model eyeground;
Model teeth;
Model horn;
void free();

// 색상
GLfloat floorColor[3] = { 0.7, 0.7, 0.7 }; // 바닥 기본 색상
GLfloat modelColor[3] = { 1.0, 1.0, 1.0 }; // 모델 기본 색상

// 사각형 바닥 그리기
void drawRect(); 

/*****************
     2번 문제
*****************/

// 뷰포트
int viewportPos[16] = {
    0, 0, 400, 400,     // 0: 앞
    400, 0, 400, 400,   // 1: 무작위
    0, 400, 400, 400,   // 2: 위
    400, 400, 400, 400  // 3: 옆
};

// 중앙 십자선 그리기 (뷰포트 구분용)
void drawLine(); 

/*****************
     3번 문제
*****************/

// 뷰포트 선택 상태 (-1은 선택되지 않음)
int viewport = -1;

// 키 입력
void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);

/*****************
     4번 문제
*****************/

// 메뉴
int light = 1; // 조명 상태 (1: 켜짐, 0: 꺼짐)
int texture = 1; // 텍스처 상태 (0: 사용 안 함, 1: 사용)
void menuCallback(int value);

// 조명 설정
GLfloat lightPosition[4] = { 20.0, 20.0, 30.0, 1.0 };
GLfloat diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };

// 텍스처
GLuint textureID[6];
void initTexture(GLuint* texture, const char* path);

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
    free();
    return 0;
}

void init() {
    dino = ObjLoad("dino.obj");
    eye = ObjLoad("eye.obj");
    eyeground = ObjLoad("eyeground.obj");
    teeth = ObjLoad("teeth.obj");
    horn = ObjLoad("horn.obj");

    glClearColor(0.2, 0.2, 0.2, 0.0);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // 감쇠율
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

    // 텍스처 이미지 불러오기
    initTexture(&textureID[0], "ground.png"); // 바닥 텍스처
    initTexture(&textureID[1], "dino.png");   // 공룡 텍스처 
    initTexture(&textureID[2], "eye.png");    // 눈 텍스처
    initTexture(&textureID[3], "eyeground.png"); // 눈 바닥 텍스처
    initTexture(&textureID[4], "teeth.png"); // 이빨 텍스처
    initTexture(&textureID[5], "horn.png"); // 뿔 텍스처
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
        glTranslatef(0.0f, -20.0f, -10.0f);
        glScalef(0.7f, 0.7f, 0.7f);
        rendering(dino, 1);
        rendering(eye, 2);
        rendering(eyeground, 3);
        rendering(teeth, 4);
        rendering(horn, 5);

        glPopMatrix();
    }

    drawLine();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void free()
{
    for (int i = 0; i < dino.vNum; i++) free(dino.vPoint[i]);
    free(dino.vPoint);
    for (int i = 0; i < dino.fNum; i++) free(dino.fPoint[i]);
    free(dino.fPoint);
    for (int i = 0; i < eye.vNum; i++)free(eye.vPoint[i]);
    free(eye.vPoint);
    for (int i = 0; i < eye.fNum; i++)free(eye.fPoint[i]);
    free(eye.fPoint);
    for (int i = 0; i < eyeground.vNum; i++)free(eyeground.vPoint[i]);
    free(eyeground.vPoint);
    for (int i = 0; i < eyeground.fNum; i++)free(eyeground.fPoint[i]);
    free(eyeground.fPoint);
    for (int i = 0; i < teeth.vNum; i++)free(teeth.vPoint[i]);
    free(teeth.vPoint);
    for (int i = 0; i < teeth.fNum; i++)free(teeth.fPoint[i]);
    free(teeth.fPoint);
    for (int i = 0; i < horn.vNum; i++)free(horn.vPoint[i]);
    free(horn.vPoint);
    for (int i = 0; i < horn.fNum; i++)free(horn.fPoint[i]);
    free(horn.fPoint);
}

void drawRect() {
    glDisable(GL_LIGHTING);
    glColor3f(floorColor[0], floorColor[1], floorColor[2]);

	// 텍스처가 활성화된 경우에만 텍스처를 사용
    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }

    glBegin(GL_QUADS);
    if (texture) glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-25.0f, -21.0f, -45.0f);
    if (texture) glTexCoord2f(1.0f, 0.0f);
    glVertex3f(25.0f, -21.0f, -45.0f);
    if (texture) glTexCoord2f(1.0f, 1.0f);
    glVertex3f(25.0f, -21.0f, 40.0f);
    if (texture) glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-25.0f, -21.0f, 40.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
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
        diffuse[0] = (float)rand() / RAND_MAX; diffuse[1] = (float)rand() / RAND_MAX; diffuse[2] = (float)rand() / RAND_MAX; // diffuse
        specular[0] = (float)rand() / RAND_MAX; specular[1] = (float)rand() / RAND_MAX; specular[2] = (float)rand() / RAND_MAX; // specular
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        printf("조명 색상 변경\n");
        break;
    case 4: // 텍스처 토글
        texture = !texture;
        if (texture) {
            printf("텍스처 On\n");
        }
        else {
            printf("텍스처 Off\n");
        }
        break;
    }
    glutPostRedisplay();
}

void initTexture(GLuint* texture, const char* path)
{
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, path);
    if (!error)
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
}