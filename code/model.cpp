#pragma warning(disable:4996)
#include "model.h"

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

    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "v ", 2) == 0) model.vNum++;
        else if (strncmp(line, "f ", 2) == 0) model.fNum++;
    }
    rewind(fp);

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

void calcNormal(double* v0, double* v1, double* v2, double* normal) {
    double u[3] = { v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2] };
    double v[3] = { v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2] };
    normal[0] = u[1] * v[2] - u[2] * v[1];
    normal[1] = u[2] * v[0] - u[0] * v[2];
    normal[2] = u[0] * v[1] - u[1] * v[0];
    double len = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (len > 0) {
        normal[0] /= len; normal[1] /= len; normal[2] /= len;
    }
}

void rendering(Model model, int sort)
{
	// 모델 색상 설정
    if (!light) {
        glDisable(GL_LIGHTING);
        glColor3f(modelColor[0], modelColor[1], modelColor[2]);
    }
    else {
        glEnable(GL_LIGHTING);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, modelColor);
    }

    // 텍스처가 활성화된 경우에만 텍스처를 사용 - 함수 시작 시 한 번만 활성화
    if (texture) {
        glEnable(GL_TEXTURE_2D);
        if(sort == 1) glBindTexture(GL_TEXTURE_2D, textureID[1]);
        if(sort == 2) glBindTexture(GL_TEXTURE_2D, textureID[2]);
        if(sort == 3) glBindTexture(GL_TEXTURE_2D, textureID[3]);
        if(sort == 4) glBindTexture(GL_TEXTURE_2D, textureID[4]);
        if(sort == 5) glBindTexture(GL_TEXTURE_2D, textureID[5]);
		if (sort == 6) glBindTexture(GL_TEXTURE_2D, textureID[6]);
		if (sort == 7) glBindTexture(GL_TEXTURE_2D, textureID[7]);
		if (sort == 8) glBindTexture(GL_TEXTURE_2D, textureID[8]);
		if (sort == 9) glBindTexture(GL_TEXTURE_2D, textureID[9]);
		if (sort == 10) glBindTexture(GL_TEXTURE_2D, textureID[10]);
		if (sort == 11) glBindTexture(GL_TEXTURE_2D, textureID[11]);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }

    for (int i = 0; i < model.fNum; i++) {
        double* v0 = model.vPoint[model.fPoint[i][0]];
        double* v1 = model.vPoint[model.fPoint[i][1]];
        double* v2 = model.vPoint[model.fPoint[i][2]];
        double normal[3];
        calcNormal(v0, v1, v2, normal);

        glBegin(GL_TRIANGLES);
        glNormal3dv(normal);

        for (int j = 0; j < 3; j++) {
            // 각 정점마다 다른 텍스처 좌표 사용 (삼각형의 위치에 따라 다름)
            if (texture) {
                // 공룡의 위치에 따라 텍스처 좌표 계산
                float u = (model.vPoint[model.fPoint[i][j]][0] + 20.0f) / 40.0f;
                float v = (model.vPoint[model.fPoint[i][j]][2] + 20.0f) / 40.0f;
                glTexCoord2f(u, v);
            }

            glVertex3f(model.vPoint[model.fPoint[i][j]][0], model.vPoint[model.fPoint[i][j]][1], model.vPoint[model.fPoint[i][j]][2]);
        }

        glEnd();
    }

    // 텍스처 상태 복원
    if (texture) {
        glDisable(GL_TEXTURE_2D);
    }
}