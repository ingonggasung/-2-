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

    static double lastRenderTime = glfwGetTime(); // 이전에 별을 출력한 시간
    static double renderInterval = 0.1; // 별을 출력하는 간격 (초 단위)

    double currentTime = glfwGetTime();
    if (currentTime - lastRenderTime >= renderInterval) {
        // 별 출력
        Star* star = new Star();
        // 랜덤한 위치와 색상 설정
        // 별 객체를 MSList에 추가
        list.add(star);

        lastRenderTime = currentTime; // 현재 시간으로 업데이트
    }

    list.renderAll();

    return 0;
}

int main(void)
{
    //glfw라이브러리 초기화
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
