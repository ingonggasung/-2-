#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
float angle = 0;
void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
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
	glVertex2f(x * cos(angle_degree) - (y * sin(angle_degree)), x * sin(angle_degree) + (y * cos(angle_degree)));
	return 0;
}

int drawQuad(float x, float y, float angle_degree)
{
	float halfWidth = x / 2;
	float halfHeight = y / 2;

	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	float x1 = (- halfWidth + 0.65f)* cosAngle - (-halfHeight * sinAngle);
	float y1 = (- halfWidth + 0.65f) * sinAngle + (-halfHeight * cosAngle);
	float x2 = (halfWidth + 0.65f)* cosAngle - (-halfHeight * sinAngle);
	float y2 = (halfWidth + 0.65f) * sinAngle + (-halfHeight * cosAngle);
	float x3 = (halfWidth + 0.65f) * cosAngle - halfHeight * sinAngle;
	float y3 = (halfWidth + 0.65f) * sinAngle + halfHeight * cosAngle;
	float x4 = (-halfWidth + 0.65f) * cosAngle - halfHeight * sinAngle;
	float y4 = (-halfWidth + 0.65f) * sinAngle + halfHeight * cosAngle;	

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3 , y3);
	glVertex2f(x4 , y4);
	glEnd();	

	return 0;
}

int drawStar(float x, float y, float angle_degree)
{
	return 0;
}



int render()
{
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(1.0f, 0.0f, 0.0f);
	setVertexRotation(0.0f, 0.0f, 0);

	for (int i = 0; i < 360; i++)
	{
		setVertexRotation(0.0f, 0.31f, angle+i);
	}

	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(1.0f, 1.0f, 0.0f);
	setVertexRotation(0.0f, 0.0f, 0);

	for (int i = 0; i < 360; i++)
	{
		setVertexRotation(0.0f, 0.3f, angle + i);
	}

	glEnd();
	drawQuad(0.1f,0.1f,angle);
	
	drawStar(0.05f, 0.05f, angle);
	angle += 0.002f;
	return 0;
}


int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

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
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}