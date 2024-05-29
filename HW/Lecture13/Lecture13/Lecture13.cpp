#pragma comment(lib, "Opengl32.lib")

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;
float moveFactor = 0.0f;
float scaleFactor = 1.0f;

float playerX = 0.0f;
float playerY = 0.0f;
float linemove = 0.0f;
int frame = 60;
float gravityacc = 0.000098f;
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

void spaceCallback(GLFWwindow* window, int key, int scancode, int action, int mods) // 스페이스 누름 감지 함수
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
    {
        int i = 0;
        while (frame>0)
        {
            i++;
            playerY += gravityacc;
            gravityacc = gravityacc + (gravityacc/ 60) * i;
            frame--;
        }
    }
}

struct Vector
{
    float x;
    float y;
};

struct collider
{
    Vector min;
    Vector max;
};

bool ColliderCheck(collider a, collider b)
{
    if (a.max.x < b.min.x || a.min.x > b.max.x) return true;
    if (a.max.y < b.min.y || a.min.y > b.max.y) return true;
    return false;
}


int line() //우에서 좌로 움직이는 선 구현
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.9995f+ linemove, 1.0f);
    glVertex2f(0.9995f+ linemove, -1.0f);
    glVertex2f(0.999f+ linemove, -1.0f);
    glVertex2f(0.999f+linemove, 1.0f);
    glEnd();
    return 0;
}
int stagerender() // 스테이지 선언
{
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(-1.0f,-0.8f);
    glVertex2f(1.0f,-0.8f);
    glVertex2f(1.0f,-1.0f);
    glVertex2f(-1.0f,-1.0f);
    glEnd();
    return 0;
}
int player() 
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.05f, -0.8f+playerY);
    glVertex2f(0.05f, -0.8f + playerY);
    glVertex2f(0.05f, -0.7f + playerY);
    glVertex2f(-0.05f, -0.7f + playerY);
    glEnd();
    return 0;
}

int main(void)
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /*  Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetKeyCallback(window, spaceCallback);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        stagerender();
        line();
        linemove -= 0.016f;
        if (linemove < -2.0f) {
            linemove = 0.0f;
        }
        player();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
