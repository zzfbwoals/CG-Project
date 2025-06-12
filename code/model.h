#pragma once

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

#ifdef __cplusplus
}
#endif
