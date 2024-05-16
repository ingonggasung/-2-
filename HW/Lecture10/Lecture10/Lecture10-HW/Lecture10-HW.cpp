#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
float earthOrbitAngle = 0.0f;
float earthRotationAngle = 0.0f; // 지구의 자전 각도
float sunRotationAngle = 0.0f; // 지구의 자전 각도
float moonOrbitAngle = 0.0f;
float angle = 0.0f;
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
    glVertex2f(x * cos(angle_degree) - (y * sin(angle_degree)), x * sin(angle_degree) + (y * cos(angle_degree)));
    return 0;
}

int setSunVertexRotation(float x, float y, float angle_degree)
{    
    glVertex2f(x * cos(angle_degree) - (y * sin(angle_degree)), x * sin(angle_degree) + (y * cos(angle_degree)));
    return 0;
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

void drawRotatedStar(float x, float y, float width, float height, float angle) {
    
}

//void drawPentagram(float x, float y, float size, float angle) {
//    float angleIncrement = 72.0 * 3.1415 / 180.0; // 72 degrees in radians
//
//    setVertexRotation(x, y, angle);
//    for (int i = 0; i < 360; i+=72)
//    {
//        setVertexRotation  
//    }
//
//    glEnd();
//}

int sunRender() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);
    setSunVertexRotation(0.0f, 0.0f, 0);

    for (int i = 0; i < 360; i++)
    {
        setSunVertexRotation(0.25f, 0.0f, i+angle);        
    }
    glEnd();   

    float posX1 = -0.1f, posY1 = -0.18f;
    for (int i = 0; i < 5; i++)
    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.8f, 0.1f);
        setVertexRotation(0.0f, -0.18f, angle);
        setVertexRotation(posX1, posY1, angle);
        posX1 = posX1 + 0.01f * i;
        posY1 = posY1 + 0.002f * (4-i);
        setVertexRotation(posX1, posY1, angle);
    }
    glEnd();
    
    float posX2 = 0.1f, posY2 = -0.18f;
    for (int i = 0; i < 5; i++)
    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.8f, 0.1f);
        setVertexRotation(0.0f, -0.18f, angle);
        setVertexRotation(posX2, posY2, angle);
        posX2 = posX2 - 0.01f * i;
        posY2 = posY2 + 0.002f * (4 - i);
        setVertexRotation(posX2, posY2, angle);
    }
    glEnd();

    float posX3 = -0.1f, posY3 = -0.18f;
    for (int i = 0; i < 5; i++)
    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.8f, 0.1f);
        setVertexRotation(0.0f, -0.18f, angle);
        setVertexRotation(posX3, posY3, angle);
        posX3 = posX3 + 0.01f * i;
        posY3 = posY3 - 0.002f * (4-i);
        setVertexRotation(posX3, posY3, angle);
    }
    glEnd();

    float posX4 = 0.1f, posY4 = -0.18f;
    for (int i = 0; i < 5; i++)
    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.8f, 0.1f);
        setVertexRotation(0.0f, -0.18f, angle);
        setVertexRotation(posX4, posY4, angle);
        posX4 = posX4 - 0.01f * i;
        posY4 = posY4 - 0.002f * (4-i);
        setVertexRotation(posX4, posY4, angle);
    }
    /*glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.8f, 0.1f);

    setVertexRotation(0.0f, -0.18f, angle);
    setVertexRotation(0.0f, -0.2f, angle);
    setVertexRotation(-0.04f, -0.198f, angle);

    setVertexRotation(0.0f, -0.18f, angle);
    setVertexRotation(-0.04f, -0.198f, angle);
    setVertexRotation(-0.07f, -0.194f, angle);

    setVertexRotation(0.0f, -0.18f, angle);
    setVertexRotation(-0.07f, -0.194f, angle);
    setVertexRotation(-0.09f, -0.188f, angle);

    setVertexRotation(0.0f, -0.18f, angle);
    setVertexRotation(-0.09f, -0.188f, angle);
    setVertexRotation(-0.1f, -0.18f, angle);*/

    glEnd();
    //x = cos(i);
    //y = sin(i);
    angle += 0.02;

    return 0;
}

int earthRender() {
    glColor3f(0.0f, 0.0f, 1.0f); // 지구는 파란색으로
    float earthX = 0.6f * cos(earthOrbitAngle);
    float earthY = 0.6f * sin(earthOrbitAngle);
    float moonX = earthX + 0.3f * cos(moonOrbitAngle);
    float moonY = earthY + 0.3f * sin(moonOrbitAngle);

    drawRotatedRectangle(earthX, earthY, 0.1f, 0.1f, earthRotationAngle); // 사각형으로 지구 그리기

    glColor3f(1.0f, 1.0f, 1.0f); // 달은 흰색으로
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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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