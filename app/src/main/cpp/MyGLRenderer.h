#ifndef MY_GL_RENDERER_H
#define MY_GL_RENDERER_H

#include <GLES3/gl3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class MyGLRenderer {
public:
    MyGLRenderer();
    GLuint vao;
    GLuint ibo;
    void onSurfaceCreated();
    void onDrawFrame();
    void onSurfaceChanged(int width, int height);
    void setRotationSpeed(float speed) {
        rotationSpeed = speed;
    }

private:
    GLuint program;
    GLuint projectionMatrixLocation; // Локация uniform-переменной для матрицы проекции
    GLuint viewMatrixLocation;       // Локация uniform-переменной для матрицы моделирования-вида
    glm::mat4 projectionMatrix;      // Матрица проекции
    glm::mat4 viewMatrix;
    float angleX = 0.0f; // Угол поворота вокруг оси X
    float angleY = 0.0f; // Угол поворота вокруг оси Y
    float rotationSpeed = 1.0f; // Скорость вращения куба
};

#endif