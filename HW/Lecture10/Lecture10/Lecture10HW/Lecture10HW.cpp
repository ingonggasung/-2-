﻿#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
float earthOrbitAngle = 0.0f;
float earthRotationAngle = 0.0f; // 지구의 자전 각도
float moonOrbitAngle = 0.0f;

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW 오류: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        moveFactor += 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        scaleFactor += 0.1f;
    }
}

int setVertexRotation(float x, float y, float angle_degree)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x * cos(angle_degree) - (y * sin(angle_degree)), x * sin(angle_degree) + (y * cos(angle_degree)));
    return 0;
}

void drawRectangle(float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(-width / 2, -height / 2);
    glVertex2f(width / 2, -height / 2);
    glVertex2f(width / 2, height / 2);
    glVertex2f(-width / 2, height / 2);
    glEnd();
}

void drawRotatedRectangle(float x, float y, float width, float height, float angle) {
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    float x1 = -halfWidth * cosAngle - (-halfHeight * sinAngle) + x;
    float y1 = -halfWidth * sinAngle + (-halfHeight * cosAngle) + y;
    float x2 = halfWidth * cosAngle - (-halfHeight * sinAngle) + x;
    float y2 = halfWidth * sinAngle + (-halfHeight * cosAngle) + y;
    float x3 = halfWidth * cosAngle - halfHeight * sinAngle + x;
    float y3 = halfWidth * sinAngle + halfHeight * cosAngle + y;
    float x4 = -halfWidth * cosAngle - halfHeight * sinAngle + x;
    float y4 = -halfWidth * sinAngle + halfHeight * cosAngle + y;

    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}


void drawStar(float x, float y, float radius, float angle) {
    const int numPoints = 5; // 별의 꼭짓점 개수
    const float angleIncrement = 2 * PI / numPoints; // 한 점에서 다음 점까지의 각도 차

    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬 모드로 설정
    glVertex2f(x, y); // 별의 중심을 첫 번째 점으로 설정

    for (int i = 0; i <= numPoints; ++i) {
        float currentAngle = angle + i * angleIncrement;
        float xOffset = radius * cos(currentAngle);
        float yOffset = radius * sin(currentAngle);
        if (i % 2 == 0) { // 홀수 번째 꼭짓점일 때는 큰 삼각형의 꼭짓점으로
            xOffset *= 0.4f; // 더 작은 삼각형을 만들기 위해 x 오프셋을 줄임
            yOffset *= 0.4f; // 더 작은 삼각형을 만들기 위해 y 오프셋을 줄임
        }
        glVertex2f(x + xOffset, y + yOffset);
    }

    glEnd();
}

void drawRotatedStar(float x, float y, float radius, float angle) {
    drawStar(x, y, radius, angle);
}

int sunRender() {
    glColor3f(1.0f, 1.0f, 0.0f); // 태양은 노란색으로
    drawRectangle(0.4f, 0.4f); // 사각형으로 태양 그리기
    return 0;
}

int earthRender() {
    glColor3f(0.0f, 0.0f, 0.0f);
    float earthX = 0.6f * cos(earthOrbitAngle);
    float earthY = 0.6f * sin(earthOrbitAngle);
    float moonX = earthX + 0.15f * cos(moonOrbitAngle);
    float moonY = earthY + 0.15f * sin(moonOrbitAngle);
    drawRotatedRectangle(earthX, earthY, 0.105f, 0.105f, earthRotationAngle); // 사각형으로 지구 그리기

    glColor3f(0.0f, 0.0f, 1.0f); // 지구는 파란색으로
    earthX = 0.6f * cos(earthOrbitAngle);
    earthY = 0.6f * sin(earthOrbitAngle);
    moonX = earthX + 0.15f * cos(moonOrbitAngle);
    moonY = earthY + 0.15f * sin(moonOrbitAngle);
    drawRotatedRectangle(earthX, earthY, 0.1f, 0.1f, earthRotationAngle); // 사각형으로 지구 그리기
    
    glColor3f(0.0f, 0.0f, 0.0f);
    drawRotatedRectangle(moonX, moonY, 0.06f, 0.06f, moonOrbitAngle);

    glColor3f(1.0f, 1.0f, 0.0f); // 달은 노란색으로
    drawRotatedRectangle(moonX, moonY, 0.05f, 0.05f, moonOrbitAngle); // 사각형으로 달 그리기


    return 0;
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

        sunRender();
        earthRender();

        // 공전 속도 설정
        earthOrbitAngle += 0.005f;
        moonOrbitAngle += 0.03f;

        // 자전 속도 설정
        earthRotationAngle += 0.01f;

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}