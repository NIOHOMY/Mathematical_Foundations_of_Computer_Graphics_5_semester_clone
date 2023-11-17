#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
GLuint vbo = 0;
GLuint vao = 0;
float points[] = {
       -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.0f, 0.4f, 0.0f, 0.7f,
       -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.0f, 0.2f, 0.2f, 0.2f
};
GLuint indices[] = {
        0, 1, 2,
        1, 3, 2
};
GLuint ebo;
GLuint vs;
GLuint fs;
GLuint shader_programme;
//GLFWwindow  *window;

const char* vertex_shader =
"#version 330 core\n" 
"layout (location = 0) in vec3 aPos;\n" 
"layout (location = 1) in vec3 aColor;\n" 
"out vec3 ourColor;\n" 
"void main()\n" 
"{\n"
"   gl_Position = vec4(aPos, 0.8);\n" 
"   ourColor = aColor;\n" 
"}\0"; 

const char* fragment_shader =
"#version 330 core\n" 
"out vec4 FragColor;\n" 
"in vec3 ourColor;\n" 
"void main()\n" 
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n" 
"}\n\0"; 

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
        /* case GLFW_KEY_SPACE:
             cur_icon_color = (cur_icon_color + 1) % 5;
             set_icon(window, cur_icon_color);
             break;
         case GLFW_KEY_X:
             glfwSetWindowIcon(window, 0, NULL);
             break;*/
    }
}

void drawGradientSquare()
{
    glUseProgram(shader_programme);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // bind shader (glUseProgrm)
    // bind vao vbo
    // bind ebo
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // release ebo
    // release vao vbo
    // release shader

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(0);

}

// Когда пользователь меняет размер окна, окно просмотра также должно быть скорректировано, требуя функцию обратного вызова
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Первые два параметра функции glViewport управляют положением нижнего левого угла окна, 
    // а третий и четвертый параметры контролируют ширину и высоту окна рендеринга
    glfwSetKeyCallback(window, key_callback);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
    // Проверка, нажимает ли пользователь клавишу возврата (Esc) (если не нажата, glfwGetKey вернет GLFW_RELEASE, если нажата, GLFW_PRESS)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char** argv)
{ 
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(900, 700, "lab 3", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    shader_programme = glCreateProgram();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);

    glLinkProgram(shader_programme);

    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawGradientSquare();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}