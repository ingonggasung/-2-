#include "MObject.h"
#include <GLFW/glfw3.h>

class Star : public MObject
{
public:
    Star();
    ~Star();

    void update();
    void render();

private:
    float x, y; // 별의 위치
    float r, g, b; // 색상
};

Star::Star() : x(0.0f), y(0.0f), r(0.0f), g(0.0f), b(0.0f) {}

Star::~Star() {}

void Star::update() {}

void Star::render()
{
    // 랜덤 위치 생성
    x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
    y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;

    // 랜덤 색상 생성
    r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex2f(x, y + 0.3f);
    glVertex2f(x - 0.13f, y - 0.25f);
    glVertex2f(x + 0.1f, y - 0.04f);

    glVertex2f(x + 0.22f, y+ 0.07f);
    glVertex2f(x-0.22f, y +0.07f);
    glVertex2f(x, y-0.12f);

    glVertex2f(x, y+ 0.3f);
    glVertex2f(x-0.1f, y-0.04f);
    glVertex2f(x+0.13f, y-0.25f);
    
    glEnd();
}