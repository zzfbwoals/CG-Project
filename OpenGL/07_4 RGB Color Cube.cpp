#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// 윈도우 및 카메라 설정
GLint winWidth = 600, winHeight = 600;
GLfloat eyeX = 0.0, eyeY = 0.0, eyeZ = 2.0;
GLfloat theta = 270.0, phi = 180.0;
GLfloat upX = 0.0, upY = 1.0, upZ = 0.0;
GLfloat r = 2.0;

// 정육면체 그리기 함수
void draw_cubde()
{
    // 앞쪽 면
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); glVertex3f(0.5, 0.5, 0.5); // White
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); // Magenta
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5); // Red
    glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, 0.5); // Yellow
    glEnd();

    // 오른쪽 면
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0); glVertex3f(0.5, 0.5, 0.5); // White
    glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, 0.5); // Yellow
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5); // Green
    glColor3f(0.0, 1.0, 1.0); glVertex3f(0.5, 0.5, -0.5); // Cyan
    glEnd();

    // 위쪽 면
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); // Magenta
    glColor3f(1.0, 1.0, 1.0); glVertex3f(0.5, 0.5, 0.5); // White
    glColor3f(0.0, 1.0, 1.0); glVertex3f(0.5, 0.5, -0.5); // Cyan
    glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); // Blue
    glEnd();

    // 왼쪽 면
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5); // Magenta
    glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5); // Blue
    glColor3f(0.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); // Black
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5); // Red
    glEnd();

    // 아래쪽 면
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5); // Red
    glColor3f(0.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5); // Black
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.5, -0.5, -0.5); // Green
    glColor3f(1.0, 1.0, 0.0); glVertex3f(0.5, -0.5, 0.5); // Yellow
    glEnd();

    // 뒤쪽 면
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.5, -0.5, -0.5); // Blue
    glColor3f(0.0, 1.0, 1.0); glVertex3f(0.5, -0.5, -0.5); // Cyan
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.5, 0.5, -0.5); // Green
    glColor3f(0.0, 0.0, 0.0); glVertex3f(-0.5, 0.5, -0.5); // Black
    glEnd();
}

// 초기화 함수
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.1, 1.1, -1.1, 1.1, 1.0, 6.0);
}

// 디스플레이 콜백
void displayFcn()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);  // set to Model View before drawing
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, upX, upY, upZ);

    glPolygonMode(GL_FRONT, GL_FILL);
    draw_cubde();

    glutSwapBuffers();
}

// 윈도우 크기 조절 콜백
void reshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    winWidth = newWidth;
    winHeight = newHeight;
}

// 마우스 위치 기반 시점 설정 -> 물체가 아닌 카메라가 돌고있는거임 구 안에 물체가 있는 느낌
// 갖다쓰셈 외우지말고
void eyePosition(void)
{
    GLfloat dt = 1.0;
    GLfloat eyeXtemp = r * sin((theta + 0.0174532 - dt) * 0.0174532) * sin(phi * 0.0174532);
    GLfloat eyeYtemp = r * cos((theta + 0.0174532 - dt) * 0.0174532);
    GLfloat eyeZtemp = r * sin((theta + 0.0174532 - dt) * 0.0174532) * cos(phi * 0.0174532);

    eyeX = r * sin(theta * 0.0174532) * sin(phi * 0.0174532);
    eyeY = r * cos(theta * 0.0174532);
    eyeZ = r * sin(theta * 0.0174532) * cos(phi * 0.0174532);

    upX = eyeXtemp - eyeX;
    upY = eyeYtemp - eyeY;
    upZ = eyeZtemp - eyeZ;

    glutPostRedisplay();
}

// 마우스 움직임 처리
void onMouseMove(int x, int y)
{
    theta = (360.0 / (double)winHeight) * (double)y * 3.0;
    phi = (360.0 / (double)winWidth) * (double)x * 3.0;
    if (theta > 360.0) theta = fmod((double)theta, 360.0);
    if (phi > 360.0) phi = fmod((double)phi, 360.0);

    eyePosition();
}

// 특수 키 입력 처리
void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) r -= 0.1;
    if (key == GLUT_KEY_DOWN) r += 0.1;
    eyePosition();
}

// 메인 함수
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Camera & RGB Color Cube");

    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(reshapeFcn);
    glutPassiveMotionFunc(onMouseMove);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
    return 0;
}
