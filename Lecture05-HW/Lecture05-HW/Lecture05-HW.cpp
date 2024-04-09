#pragma comment(lib, "Opengl32.lib")  // OpenGL 라이브러리 링크를 위한 pragma 지시문

#include <GLFW/glfw3.h>  // GLFW 라이브러리를 사용하기 위한 헤더 파일 포함
#include <iostream>     // 표준 입력 및 출력을 위한 헤더 파일 포함

float moveFactor = 0.0f;      // 별의 이동 요인을 저장하는 변수
float scaleFactor = 1.0f;     // 별의 크기 변화 요인을 저장하는 변수
double prevMouseX, prevMouseY;   // 이전 마우스 좌표를 저장하는 변수
bool isLeftButtonPressed = false;   // 왼쪽 마우스 버튼 상태를 저장하는 변수
bool isRightButtonPressed = false;  // 오른쪽 마우스 버튼 상태를 저장하는 변수
float starCenterX = 0.0f;       // 별의 중심 X 좌표를 저장하는 변수
float starCenterY = 0.0f;       // 별의 중심 Y 좌표를 저장하는 변수

// GLFW 오류 콜백 함수
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;  // 오류 메시지 출력
}

// 마우스 버튼 콜백 함수
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)  // 왼쪽 마우스 버튼이 눌렸을 때
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);  // 현재 마우스 좌표를 가져옴
        prevMouseX = mouseX;   // 이전 마우스 X 좌표 업데이트
        prevMouseY = mouseY;   // 이전 마우스 Y 좌표 업데이트
        isLeftButtonPressed = true;   // 왼쪽 마우스 버튼 상태를 눌림으로 설정
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) // 왼쪽 마우스 버튼이 떼어졌을 때
    {
        isLeftButtonPressed = false;  // 왼쪽 마우스 버튼 상태를 떼어짐으로 설정
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)  // 오른쪽 마우스 버튼이 눌렸을 때
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);  // 현재 마우스 좌표를 가져옴
        prevMouseX = mouseX;   // 이전 마우스 X 좌표 업데이트
        prevMouseY = mouseY;   // 이전 마우스 Y 좌표 업데이트
        isRightButtonPressed = true;  // 오른쪽 마우스 버튼 상태를 눌림으로 설정
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)  // 오른쪽 마우스 버튼이 떼어졌을 때
    {
        isRightButtonPressed = false; // 오른쪽 마우스 버튼 상태를 떼어짐으로 설정
    }
}

// 마우스 커서 위치 콜백 함수
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{

    if (isLeftButtonPressed)  // 왼쪽 마우스 버튼이 눌려 있을 때
    {
        moveFactor -= (ypos - prevMouseY) / 400.0f;   // 이동 요인 계산 및 업데이트
        starCenterY -= (ypos - prevMouseY) / 400.0f;  // 별의 중심 Y 좌표 업데이트
        starCenterX += (xpos - prevMouseX) / 400.0f;  // 별의 중심 X 좌표 업데이트
        prevMouseX = xpos;    // 이전 마우스 X 좌표 업데이트
        prevMouseY = ypos;    // 이전 마우스 Y 좌표 업데이트
    }
    else if (isRightButtonPressed) // 오른쪽 마우스 버튼이 눌려 있을 때
    {
        double deltaX = xpos - prevMouseX;
        double scaleFactorChange = deltaX / 400.0f; // 확대/축소 요인 계산
        scaleFactor += scaleFactorChange; // 확대/축소 요인 업데이트
        prevMouseX = xpos;  // 이전 마우스 X 좌표 업데이트
        prevMouseY = ypos;  // 이전 마우스 Y 좌표 업데이트
    }
}

// 별을 그리는 함수
void render()
{
    glBegin(GL_POLYGON);   // 다각형 그리기 시작

    glColor3f(1.0f, 1.0f, 1.0f);  // 흰색으로 색상 설정

    // 별의 각 꼭짓점을 계산하여 정점을 그림
    glVertex2f((0.0f + starCenterX) * scaleFactor, (-0.5f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((0.5f + starCenterX) * scaleFactor, (-0.8f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((0.3f + starCenterX) * scaleFactor, (-0.3f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((0.8f + starCenterX) * scaleFactor, (0.1f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((0.2f + starCenterX) * scaleFactor, (0.1f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((0.0f + starCenterX) * scaleFactor, (0.8f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((-0.2f + starCenterX) * scaleFactor, (0.1f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((-0.8f + starCenterX) * scaleFactor, (0.1f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((-0.3f + starCenterX) * scaleFactor, (-0.3f + starCenterY + moveFactor) * scaleFactor);
    glVertex2f((-0.5f + starCenterX) * scaleFactor, (-0.8f + starCenterY + moveFactor) * scaleFactor);

    glEnd();  // 다각형 그리기 종료
}

// 프로그램의 메인 함수
int main(void)
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;  // 윈도우 핸들러 변수 선언
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);  // 윈도우 생성

    if (!window)  // 윈도우 생성 실패 시
    {
        glfwTerminate();  // GLFW 종료
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);  // 현재 윈도우의 컨텍스트를 활성화
    glfwSetErrorCallback(errorCallback);  // 오류 콜백 함수 설정
    glfwSetMouseButtonCallback(window, mouseButtonCallback);  // 마우스 버튼 콜백 함수 설정
    glfwSetCursorPosCallback(window, cursorPosCallback);  // 마우스 커서 위치 콜백 함수 설정

    while (!glfwWindowShouldClose(window))  // 윈도우가 닫히지 않는 동안 반복
    {
        glfwPollEvents();  // 이벤트 처리
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);  // 배경색 설정
        glClear(GL_COLOR_BUFFER_BIT);  // 버퍼 클리어

        render();  // 별을 그리는 함수 호출

        glfwSwapBuffers(window);  // 프론트 버퍼와 백 버퍼 교환
    }

    glfwTerminate();  // GLFW 종료
    return 0;
}