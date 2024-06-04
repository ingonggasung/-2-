#pragma comment(lib, "Opengl32.lib")

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

float playerX = 0.0f;
float playerY = 0.0f;
float linemove = 0.0f;
const float gravity = -0.0001f;
const float jumpVelocity = 0.015f;
float playerVelocityY = 0.0f;
bool isJumping = false;

void errorCallback(int error, const char* description) {
    std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping) {
        playerVelocityY = jumpVelocity;
        isJumping = true;
    }
}

struct Vector {
    float x;
    float y;
};

struct collider {
    Vector min;
    Vector max;
};

bool ColliderCheck(collider a, collider b) {
    if (a.max.x < b.min.x || a.min.x > b.max.x) return true;
    if (a.max.y < b.min.y || a.min.y > b.max.y) return true;
    return false;
}

int line() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.9995f + linemove, 1.0f);
    glVertex2f(0.9995f + linemove, -1.0f);
    glVertex2f(0.999f + linemove, -1.0f);
    glVertex2f(0.999f + linemove, 1.0f);
    glEnd();
    return 0;
}

int stagerender() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, -0.8f);
    glVertex2f(1.0f, -0.8f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    return 0;
}

int player() {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.05f, -0.8f + playerY);
    glVertex2f(0.05f, -0.8f + playerY);
    glVertex2f(0.05f, -0.7f + playerY);
    glVertex2f(-0.05f, -0.7f + playerY);
    glEnd();
    return 0;
}

void updatePlayer() {
    playerVelocityY += gravity;
    playerY += playerVelocityY;

    if (playerY <= 0.0f) {
        playerY = 0.0f;
        playerVelocityY = 0.0f;
        isJumping = false;
    }
}

int main(void) {
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        updatePlayer();

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
