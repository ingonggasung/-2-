#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

float scaleFactor = 1.0f;
float shapeX = 0.0f;
float shapeY = 0.0f;
bool isMouseLeftClicked = false;
bool isMouseRightClicked = false;
double lastX = 0.0;
double lastY = 0.0;

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
        shapeY += 0.01f;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        shapeY -= 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        shapeX += 0.01f;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        shapeX -= 0.01f;
    }
}

void mouseDrag(GLFWwindow* window, double xpos, double ypos)
{
    if (isMouseLeftClicked) {
        // 마우스가 눌린 상태에서만 도형의 중심을 마우스 커서 위치로 업데이트합니다.
        shapeX = (float)(xpos / 1280.0 - 0.5); // 윈도우의 너비로 정규화하고 도형의 중심 설정
        shapeY = (float)(0.5 - ypos / 768.0); // 윈도우의 높이로 정규화하고 도형의 중심 설정
    }
    if (isMouseRightClicked) {
        double xOffset = xpos - lastX;
        double yOffset = lastY - ypos; // y 좌표는 반전

        if (xOffset > 0) {
            // 우측으로 드래그하면 도형의 크기 증가
            scaleFactor += 0.01f;
        }
        else if (xOffset < 0) {
            // 좌측으로 드래그하면 도형의 크기 감소
            scaleFactor -= 0.01f;
        }

        // 최소 크기를 설정
        scaleFactor = std::max(scaleFactor, 0.1f);

        lastX = xpos;
        lastY = ypos;
    }
}

void mouseDown(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // 마우스 왼쪽 버튼 누름 감지
        isMouseLeftClicked = true;
        double clickX, clickY;
        glfwGetCursorPos(window, &clickX, &clickY);
        shapeX = (float)(clickX / 1280.0 - 0.5); // 윈도우의 너비로 정규화하고 도형의 중심 설정
        shapeY = (float)(0.5 - clickY / 768.0); // 윈도우의 높이로 정규화하고 도형의 중심 설정
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        // 마우스 왼쪽 버튼 놓음 감지
        isMouseLeftClicked = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        // 마우스 오른쪽 버튼 누름 감지
        isMouseRightClicked = true;
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        // 마우스 오른쪽 버튼 놓음 감지
        isMouseRightClicked = false;
    }
}

int render() // 도형 선언
{
    glLoadIdentity(); // 변환을 초기화합니다.

    // 이동 및 크기 조정
    glTranslatef(shapeX, shapeY, 0.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.17f, -0.5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.135f, -0.082f);

    //=========================

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.315f, 0.145f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.315f, 0.145f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, -0.265f);

    //=========================

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.17f, -0.5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.135f, -0.082f);

    glEnd();

    return 0;
}

int main(void)
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /*  Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseDown); // 마우스 클릭
    glfwSetCursorPosCallback(window, mouseDrag); // 마우스 이동

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
