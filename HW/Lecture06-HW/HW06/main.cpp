#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include "MSList.h"
#include "Star.hpp"

MSList list;

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
    std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
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

int initialize()
{
    srand(static_cast<unsigned int>(time(NULL)));

    return 0;
}

int release()
{
    return 0;
}

int render()
{
    glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static double lastRenderTime = glfwGetTime(); // ������ ���� ����� �ð�
    static double renderInterval = 0.1; // ���� ����ϴ� ���� (�� ����)

    double currentTime = glfwGetTime();
    if (currentTime - lastRenderTime >= renderInterval) {
        // �� ���
        Star* star = new Star();
        // ������ ��ġ�� ���� ����
        // �� ��ü�� MSList�� �߰�
        list.add(star);

        lastRenderTime = currentTime; // ���� �ð����� ������Ʈ
    }

    list.renderAll();

    return 0;
}

int main(void)
{
    //glfw���̺귯�� �ʱ�ȭ
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    initialize();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        render();
        glfwSwapBuffers(window);
    }

    release();

    glfwTerminate();
    return 0;

}
