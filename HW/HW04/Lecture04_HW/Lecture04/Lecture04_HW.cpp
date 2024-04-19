//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색

#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

void errorCallback(int error, const char* description) // 오류 감지 함수
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) // esc키를 누르면 화면이 꺼지게 설정하는 함수
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouseDown(GLFWwindow* window, int key, int action, int mods)  // 마우스 버튼 클릭감지 함수
{
	if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) // 오른버튼 누르면 빨간색으로 변환
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) // 왼버튼 누르면 녹색으로 변환
	{
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void mouseMove(GLFWwindow* window, double xpos,double ypos)
{
	int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int rightState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

	if (rightState == GLFW_PRESS) // 왼쪽, 오른쪽 버튼을 누른 상태에서 드래그 중
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 파란색
	}
	else if (leftState == GLFW_PRESS) // 왼쪽 버튼을 누른 상태에서 드래그 중
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 마젠타색
	}
}

int main(void)
{
	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "abcd", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseDown); // 마우스 클릭
	glfwSetCursorPosCallback(window, mouseMove); // 마우스 움직임

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();		
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}