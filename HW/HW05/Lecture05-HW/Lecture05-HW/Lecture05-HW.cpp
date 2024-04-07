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
    std::cerr << "GLFW ����: " << description << std::endl;
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
        // ���콺�� ���� ���¿����� ������ �߽��� ���콺 Ŀ�� ��ġ�� ������Ʈ�մϴ�.
        shapeX = (float)(xpos / 1280.0 - 0.5); // �������� �ʺ�� ����ȭ�ϰ� ������ �߽� ����
        shapeY = (float)(0.5 - ypos / 768.0); // �������� ���̷� ����ȭ�ϰ� ������ �߽� ����
    }
    if (isMouseRightClicked) {
        double xOffset = xpos - lastX;
        double yOffset = lastY - ypos; // y ��ǥ�� ����

        if (xOffset > 0) {
            // �������� �巡���ϸ� ������ ũ�� ����
            scaleFactor += 0.01f;
        }
        else if (xOffset < 0) {
            // �������� �巡���ϸ� ������ ũ�� ����
            scaleFactor -= 0.01f;
        }

        // �ּ� ũ�⸦ ����
        scaleFactor = std::max(scaleFactor, 0.1f);

        lastX = xpos;
        lastY = ypos;
    }
}

void mouseDown(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // ���콺 ���� ��ư ���� ����
        isMouseLeftClicked = true;
        double clickX, clickY;
        glfwGetCursorPos(window, &clickX, &clickY);
        shapeX = (float)(clickX / 1280.0 - 0.5); // �������� �ʺ�� ����ȭ�ϰ� ������ �߽� ����
        shapeY = (float)(0.5 - clickY / 768.0); // �������� ���̷� ����ȭ�ϰ� ������ �߽� ����
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        // ���콺 ���� ��ư ���� ����
        isMouseLeftClicked = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        // ���콺 ������ ��ư ���� ����
        isMouseRightClicked = true;
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        // ���콺 ������ ��ư ���� ����
        isMouseRightClicked = false;
    }
}

int render() // ���� ����
{
    glLoadIdentity(); // ��ȯ�� �ʱ�ȭ�մϴ�.

    // �̵� �� ũ�� ����
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
    // GLFW ���̺귯�� �ʱ�ȭ
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
    glfwSetMouseButtonCallback(window, mouseDown); // ���콺 Ŭ��
    glfwSetCursorPosCallback(window, mouseDrag); // ���콺 �̵�

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
