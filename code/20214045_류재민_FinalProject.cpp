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
Model rleg;
Model lleg;
Model legCover;
Model rarm;
Model larm;
Model armCover;
void free();
void drawModel();

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
float lightMoveSpeed = 1.0f; // 조명 이동 속도

// 텍스처
GLuint textureID[12];
void initTexture(GLuint* texture, const char* path);

/*****************
     5번 문제
*****************/

// 애니메이션
float baseAmplitude = 1.5f; // 기본 진폭
float speed = 20.0f; // 애니메이션 속도
float animAngle = 0.0f; // 애니메이션 각도
int animDirection = 1; // 애니메이션 방향 (1: 증가, -1: 감소)
int animation = 0; // 애니메이션 상태 (1: 켜짐, 0: 꺼짐)
void animate(int value);

// 그리드
int grid = 0; // 그리드 상태 (1: 켜짐, 0: 꺼짐)
void drawGrid();

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
    glutTimerFunc(0, animate, 0);
    glutMainLoop();
    free();
    return 0;
}

void init() {
    // 모델 불러오기
    dino = ObjLoad("dino.obj");
    eye = ObjLoad("eye.obj");
    eyeground = ObjLoad("eyeground.obj");
    teeth = ObjLoad("teeth.obj");
    horn = ObjLoad("horn.obj");
    rleg = ObjLoad("rleg.obj");
    lleg = ObjLoad("lleg.obj");
    legCover = ObjLoad("legCover.obj");
    rarm = ObjLoad("rarm.obj");
    larm = ObjLoad("larm.obj");
    armCover = ObjLoad("armCover.obj");

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
    glutAddMenuEntry("애니메이션 On/Off", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // 텍스처 이미지 불러오기
    initTexture(&textureID[0], "ground.png"); // 바닥 텍스처
    initTexture(&textureID[1], "dino.png");   // 공룡 텍스처 
    initTexture(&textureID[2], "eye.png");    // 눈 텍스처
    initTexture(&textureID[3], "eyeground.png"); // 눈 바닥 텍스처
    initTexture(&textureID[4], "teeth.png"); // 이빨 텍스처
    initTexture(&textureID[5], "horn.png"); // 뿔 텍스처
    initTexture(&textureID[6], "dino.png"); // 오른다리 텍스처
    initTexture(&textureID[7], "dino.png"); // 왼다리 텍스처
    initTexture(&textureID[8], "dino.png"); // 다리 커버 텍스처
    initTexture(&textureID[9], "dino.png"); // 오른팔 텍스처
    initTexture(&textureID[10], "dino.png"); // 왼팔 텍스처
    initTexture(&textureID[11], "dino.png"); // 팔 커버 텍스처
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

        // 조명 설정 (카메라 뷰 적용 후 조명 위치 설정)
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // 조명 그리기
        if (light) {
            glDisable(GL_LIGHTING);
            glPushMatrix();
            glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
            glColor3f(0.0, 0.0, 0.0);
            glutWireCube(2.0);
            glPopMatrix();
            glEnable(GL_LIGHTING);
        }

        // 사각형 바닥 그리기
        glPushMatrix();
        drawRect();
        glPopMatrix();

        // 그리드 그리기
        if (grid) {
            glPushMatrix();
            drawGrid();
            glPopMatrix();
        }

        // 모델 그리기
        drawModel();

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
    for (int i = 0; i < rleg.vNum; i++)free(rleg.vPoint[i]);
    free(rleg.vPoint);
    for (int i = 0; i < rleg.fNum; i++)free(rleg.fPoint[i]);
    free(rleg.fPoint);
    for (int i = 0; i < lleg.vNum; i++)free(lleg.vPoint[i]);
    free(lleg.vPoint);
    for (int i = 0; i < lleg.fNum; i++)free(lleg.fPoint[i]);
    free(lleg.fPoint);
    for (int i = 0; i < legCover.vNum; i++)free(legCover.vPoint[i]);
    free(legCover.vPoint);
    for (int i = 0; i < legCover.fNum; i++)free(legCover.fPoint[i]);
    free(legCover.fPoint);
    for (int i = 0; i < rarm.vNum; i++)free(rarm.vPoint[i]);
    free(rarm.vPoint);
    for (int i = 0; i < rarm.fNum; i++)free(rarm.fPoint[i]);
    free(rarm.fPoint);
    for (int i = 0; i < larm.vNum; i++)free(larm.vPoint[i]);
    free(larm.vPoint);
    for (int i = 0; i < larm.fNum; i++)free(larm.fPoint[i]);
    free(larm.fPoint);
    for (int i = 0; i < armCover.vNum; i++)free(armCover.vPoint[i]);
    free(armCover.vPoint);
    for (int i = 0; i < armCover.fNum; i++)free(armCover.fPoint[i]);
    free(armCover.fPoint);
}

void drawModel()
{
    glTranslatef(0.0f, -20.0f, -10.0f);
    glScalef(0.7f, 0.7f, 0.7f);
    if (animation) glRotatef(animAngle, 0.0f, 1.0f, 0.5f); // 회전 애니메이션

    // 몸통 (dino)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f), 0.0f);
    rendering(dino, 1);
    glPopMatrix();

    // 눈 (eye)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f), 0.0f);
    rendering(eye, 2);
    glPopMatrix();

    // 눈 흰자 (eyeground)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f), 0.0f);
    rendering(eyeground, 3);
    glPopMatrix();

    // 이빨 (teeth)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f), 0.0f);
    rendering(teeth, 4);
    glPopMatrix();

    // 뿔 (horn)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f), 0.0f);
    rendering(horn, 5);
    glPopMatrix();

    // 커버는 진폭으로 인해 비워지는 공간을 메우기 위해 사용하므로 진폭 애니메이션 X
    rendering(legCover, 8);
    rendering(armCover, 11);

    // 오른쪽 다리(rleg)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -(baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f)), 0.0f); // 아래로만 이동
    rendering(rleg, 6);
    glPopMatrix();

    // 왼쪽 다리(lleg) - 반대 위상
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -(baseAmplitude * (sinf((animAngle + 180.0f) * 3.14159f / speed) * 0.5f + 0.5f)), 0.0f); // 반대 위상
    rendering(lleg, 7);
    glPopMatrix();

    // 오른쪽 팔(rarm)
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -(baseAmplitude * (sinf((animAngle + 180.0f) * 3.14159f / speed) * 0.5f + 0.5f)), 0.0f); // 반대 위상
    rendering(rarm, 9);
    glPopMatrix();

    // 왼쪽 팔(larm) - 반대 위상
    glPushMatrix();
    if (animation) glTranslatef(0.0f, -(baseAmplitude * (sinf(animAngle * 3.14159f / speed) * 0.5f + 0.5f)), 0.0f); // 아래로만 이동
    rendering(larm, 10);
    glPopMatrix();
}

void drawRect() {
    glEnable(GL_LIGHTING);

	// 바닥 색상 설정
    if (!light) {
        glDisable(GL_LIGHTING);
        glColor3f(floorColor[0], floorColor[1], floorColor[2]);
    }
    else {
        glEnable(GL_LIGHTING);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, floorColor);
    }

    // 텍스처가 활성화된 경우
    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);
        // 텍스처와 조명 조합 모드 설정
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }

    // 사각형 바닥 그리기
    glBegin(GL_QUADS);
    // 법선 벡터 설정 (바닥은 위를 향하므로 (0, 1, 0))
    glNormal3f(0.0f, 1.0f, 0.0f);
    if (texture) glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-25.0f, -21.0f, -45.0f);
    if (texture) glTexCoord2f(1.0f, 0.0f);
    glVertex3f(25.0f, -21.0f, -45.0f);
    if (texture) glTexCoord2f(1.0f, 1.0f);
    glVertex3f(25.0f, -21.0f, 40.0f);
    if (texture) glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-25.0f, -21.0f, 40.0f);
    glEnd();

    // 텍스처 비활성화
    if (texture) {
        glDisable(GL_TEXTURE_2D);
    }
}

void drawGrid() {
    glDisable(GL_LIGHTING); 
    glDisable(GL_TEXTURE_2D); 
    glLineWidth(1.0f); 

    // 일반 격자선 (회색)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (float x = -50.0f; x <= 50.0f; x += 5.0f) {
        if (x != 0.0f) { // 중앙선은 제외
			glVertex3f(x, -20.9f, -50.0f); // 바닥 바로 위에 위치
            glVertex3f(x, -20.9f, 50.0f);
        }
    }
    for (float z = -50.0f; z <= 50.0f; z += 5.0f) {
        if (z != 0.0f) { // 중앙선은 제외
            glVertex3f(-50.0f, -20.9f, z);
            glVertex3f(50.0f, -20.9f, z);
        }
    }
    glEnd();

    // 중앙 십자선 (검은색)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -20.9f, -50.0f);
    glVertex3f(0.0f, -20.9f, 50.0f);
    glVertex3f(-50.0f, -20.9f, 0.0f);
    glVertex3f(50.0f, -20.9f, 0.0f);
    glEnd();

    glEnable(GL_LIGHTING); // 조명 복원
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
        printf("뷰포트 선택: 위\n");
        break;
    case '2':
        viewport = 3; // 옆
        printf("뷰포트 선택: 옆\n");
        break;
    case '3':
        viewport = 0; // 앞
        printf("뷰포트 선택: 앞\n");
        break;
    case '4':
        viewport = 1; // 무작위
        printf("뷰포트 선택: 무작위\n");
        break;
    case 'x':
        lightPosition[0] += lightMoveSpeed;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        break;
    case 'X':
        lightPosition[0] -= lightMoveSpeed;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        break;
    case 'y':
        lightPosition[1] += lightMoveSpeed;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        break;
    case 'Y':
        lightPosition[1] -= lightMoveSpeed;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        break;
    case 'z':
        lightPosition[2] -= lightMoveSpeed;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        break;
    case 'Z':
        lightPosition[2] += lightMoveSpeed;
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        break;
    case 'g':
    case 'G':
        grid = !grid; // 그리드 토글
        printf("그리드 %s\n", grid ? "On" : "Off");
        break;
    case 'f':
    case 'F':
        if (viewport != -1) {
            initCamera(0); // 앞쪽 뷰 설정
            cameras[viewport] = cameras[0]; // 현재 뷰포트에 복사
            eyePosition(viewport);
            printf("카메라: 앞쪽 뷰 (뷰포트 %d)\n", viewport);
        }
        break;
    case 'b':
    case 'B':
        if (viewport != -1) {
            initCamera(0); // 앞쪽 뷰 설정
            cameras[viewport] = cameras[0];
            cameras[viewport].phi += 180.0f; // 뒤쪽으로 180도 회전
            if (cameras[viewport].phi > 360.0) cameras[viewport].phi = fmod((double)cameras[viewport].phi, 360.0);
            eyePosition(viewport);
            printf("카메라: 뒤쪽 뷰 (뷰포트 %d)\n", viewport);
        }
        break;
    case 'l':
    case 'L':
        if (viewport != -1) {
            initCamera(3); // 옆쪽 뷰 설정
            cameras[viewport] = cameras[3];
            eyePosition(viewport);
            printf("카메라: 옆쪽 뷰 (뷰포트 %d)\n", viewport);
        }
        break;
    case 'u':
    case 'U':
        if (viewport != -1) {
            initCamera(2); // 위쪽 뷰 설정
            cameras[viewport] = cameras[2];
            eyePosition(viewport);
            printf("카메라: 위쪽 뷰 (뷰포트 %d)\n", viewport);
        }
        break;
    case 'p':
    case 'P':
        if (viewport != -1) {
            initCamera(1); // 무작위 뷰 설정
            cameras[viewport] = cameras[1];
            eyePosition(viewport);
            printf("카메라: 무작위 뷰 (뷰포트 %d)\n", viewport);
        }
        break;
    }
    glutPostRedisplay();
}

void menuCallback(int value) {
    switch (value) {
    case 0: // 바닥 색상 변경
        floorColor[0] = (float)rand() / RAND_MAX;
        floorColor[1] = (float)rand() / RAND_MAX;
        floorColor[2] = (float)rand() / RAND_MAX;
        printf("바닥 색상 변경: RGB(%.2f, %.2f, %.2f)\n", floorColor[0], floorColor[1], floorColor[2]);
        break;
    case 1: // 모델 색상 변경
        modelColor[0] = (float)rand() / RAND_MAX;
        modelColor[1] = (float)rand() / RAND_MAX;
        modelColor[2] = (float)rand() / RAND_MAX;
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
        diffuse[0] = (float)rand() / RAND_MAX;
        diffuse[1] = (float)rand() / RAND_MAX;
        diffuse[2] = (float)rand() / RAND_MAX;
        specular[0] = (float)rand() / RAND_MAX;
        specular[1] = (float)rand() / RAND_MAX;
        specular[2] = (float)rand() / RAND_MAX;
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
    case 5: // 애니메이션 토글
        animation = !animation;
        if (animation) {
            printf("애니메이션 On\n");
            glutTimerFunc(0, animate, 0);
        }
        else {
            printf("애니메이션 Off\n");
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

void animate(int value) {
    if (animation) {
        // -5도 ~ 5도 사이를 오감
        if (animAngle > 5.0f) animDirection = -1;
        if (animAngle < -5.0f) animDirection = 1;

        animAngle += animDirection * 0.4f;

        glutPostRedisplay();
        glutTimerFunc(16, animate, 0);
    }
}