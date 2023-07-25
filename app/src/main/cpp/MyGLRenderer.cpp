#include "MyGLRenderer.h"

// Шейдеры для рисования куба
const char* vertexShaderCode =
        "#version 300 es\n"
        "layout(location = 0) in vec4 vPosition;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "}\n";

const char* fragmentShaderCode =
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "  fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n" // Красный цвет
        "}\n";
MyGLRenderer::MyGLRenderer() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    // Создание программы и привязка шейдеров
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Удаление шейдеров
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Создание VAO (Vertex Array Object) и буфер для вершин
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);

// Задаем координаты вершин для куба
    float vertices[] = {
            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f
    };

    GLuint indices[] = {
            0, 1, 2, // Первая грань (передняя)
            2, 3, 0,

            1, 5, 6, // Вторая грань (правая)
            6, 2, 1,

            7, 6, 5, // Третья грань (задняя)
            5, 4, 7,

            4, 0, 3, // Четвертая грань (левая)
            3, 7, 4,

            4, 5, 1, // Пятая грань (верхняя)
            1, 0, 4,

            3, 2, 6, // Шестая грань (нижняя)
            6, 7, 3
    };

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Атрибут позиции вершин
    GLint posAttrib = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Отвязка VAO и VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
    viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 3.0f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(4.0f, 1.0f, 2.0f));
}

void MyGLRenderer::onSurfaceCreated() {
    // Здесь выполняется инициализация, например, установка цвета фона
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void MyGLRenderer::onDrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Включаем программу шейдеров
    glUseProgram(program);

    // Передаем матрицы в шейдеры
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Привязываем VAO и IBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    angleX += rotationSpeed;
    angleY += rotationSpeed;

    // Вычисление матрицы вида с учетом вращения
    glm::mat4 viewRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    viewRotationMatrix = glm::rotate(viewRotationMatrix, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 viewMatrixWithRotation = viewMatrix * viewRotationMatrix;

    // Передаем обновленную матрицу вида в шейдеры
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrixWithRotation));


    // Отрисовываем куб с использованием индексного буфера
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Отвязываем IBO и VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Отключаем программу шейдеров
    glUseProgram(0);
}







void MyGLRenderer::onSurfaceChanged(int width, int height) {
    // Здесь выполняется обработка изменения размеров окна отображения
    glViewport(0, 0, width, height);
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    // Задаем матрицу проекции, например, перспективную проекцию
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}