#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW 오류: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        moveFactor += 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scaleFactor += 0.1f;
    }
}

int setVertexRotation(float x, float y, float angle_degree)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x * cos(angle_degree) - (y * sin(angle_degree)), x * sin(angle_degree) + (y * cos(angle_degree)));
    return 0;
}

float angle = 0;

int render() // 도형 선언
{
    glBegin(GL_TRIANGLES);

    setVertexRotation(0.45f, 0.14f, angle);
    setVertexRotation(-0.45f, 0.14f, angle);
    setVertexRotation(0.0f, -0.2f, angle);

    setVertexRotation(0.0f, 0.45f, angle);
    setVertexRotation(-0.27f, -0.44f, angle);
    setVertexRotation(0.15f, -0.1f, angle);

    setVertexRotation(0.0f, 0.45f, angle);
    setVertexRotation(-0.15f, -0.1f, angle);
    setVertexRotation(0.27f, -0.44f, angle);

    glEnd();

    angle += 0.02;

    return 0;
}

int main(void)
{
    //glfw라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 800, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;

}