#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

// 색깔 상수 정의
const float RED[] = { 1.0f, 0.0f, 0.0f, 0.0f };
const float GREEN[] = { 0.0f, 1.0f, 0.0f, 0.0f };
const float BLUE[] = { 0.0f, 0.0f, 1.0f, 0.0f };
const float MAGENTA[] = { 1.0f, 0.0f, 1.0f, 0.0f };
const float BLACK[] = { 0.0f, 0.0f, 0.0f, 0.0f };

// 현재 색깔을 저장하는 변수
const float* currentColor = BLACK;

// GLFW 오류 콜백 함수
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

// 키 콜백 함수
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// 마우스 버튼 콜백 함수
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
            currentColor = RED; // 마우스 오른쪽 버튼 누를 때 빨간색
        else if (action == GLFW_RELEASE)
            currentColor = BLACK; // 마우스 오른쪽 버튼 뗄 때 원상복구
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            currentColor = GREEN; // 마우스 왼쪽 버튼 누를 때 녹색
        else if (action == GLFW_RELEASE)
            currentColor = BLACK; // 마우스 왼쪽 버튼 뗄 때 원상복구
    }
}

// 마우스 이동 콜백 함수
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    int rightButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int leftButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if (rightButtonState == GLFW_PRESS)
    {
        currentColor = BLUE; // 오른쪽 버튼을 누르고 드래그 중이면 파란색
    }
    else if (leftButtonState == GLFW_PRESS)
    {
        currentColor = MAGENTA; // 왼쪽 버튼을 누르고 드래그 중이면 마젠타색
    }
    else
    {
        currentColor = BLACK; // 아무 버튼도 누르지 않으면 검은색
    }
}

int main(void)
{
    if (!glfwInit()) // GLFW 라이브러리 초기화
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL); // 1280x768 크기의 창 생성

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // 창의 OpenGL 컨텍스트를 현재 컨텍스트로 설정
    glfwMakeContextCurrent(window);

    // 오류 콜백 함수 설정
    glfwSetErrorCallback(errorCallback);

    // 키 콜백 함수 설정
    glfwSetKeyCallback(window, keyCallback);

    // 마우스 버튼 콜백 함수 설정
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // 마우스 이동 콜백 함수 설정
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    while (!glfwWindowShouldClose(window)) // 창이 닫혀야 하는지 확인
    {
        glClearColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]); // 현재 색으로 창 지우기
        glClear(GL_COLOR_BUFFER_BIT); // 버퍼 지우기

        glfwSwapBuffers(window); // 프론트 버퍼와 백 버퍼 교체
        glfwPollEvents(); // 이벤트 처리
    }

    glfwTerminate(); // GLFW 종료
    return 0;
}