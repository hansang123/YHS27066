#pragma comment (lib, "OpenGL32.lib")

#include <GLFW/glfw3.h> 
#include <iostream> 

bool rightbtnDown = false; 
bool leftbtnDown = false; 
bool rightbtnDownDragging = false;
bool leftbtnDownDragging = false; 
double lastYPos = 0.0; // 마지막 Y 위치 저장 변수

double xpos = 0.0; 
double ypos = 0.0; 

// 마우스 버튼 콜백 함수 정의
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
   
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) { 
            rightbtnDown = true;
            rightbtnDownDragging = false; // 드래그 상태 초기화
        }
        else if (action == GLFW_RELEASE) // 떼어짐 이벤트
            rightbtnDown = false; // 오른쪽 마우스 버튼이 떼어짐
    }
    // 왼쪽 마우스 버튼
    else if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) { 
            leftbtnDown = true; 
            leftbtnDownDragging = false; // 드래그 상태 초기화
        }
        else if (action == GLFW_RELEASE) // 떼어짐 이벤트
            leftbtnDown = false; // 왼쪽 마우스 버튼이 떼어짐
    }
}

// 마우스 커서 위치 콜백 함수 정의
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    // 오른쪽 마우스 버튼이 눌려 있고 드래그 중일 때
    if (rightbtnDown && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        rightbtnDownDragging = true; // 
        leftbtnDownDragging = false; // 
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 파란색 배경
    }
    // 왼쪽 마우스 버튼이 눌려 있고 드래그 중일 때
    else if (leftbtnDown && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        rightbtnDownDragging = false; // 
        leftbtnDownDragging = true; // 
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 보라색 배경
    }
    else { // 그 외의 경우
        rightbtnDownDragging = false; // 오른쪽 마우스 버튼 드래그 아님
        lastYPos = 0.0; // 마지막 Y 위치 초기화
    }

    glClear(GL_COLOR_BUFFER_BIT); // 버퍼를 지우고 새로운 프레임을 그림
    glfwSwapBuffers(window); // 프레임을 화면에 표시
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl; // 오류 메시지 출력
        return -1; // 프로그램 종료
    }

    // GLFW 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl; // 오류 메시지 출력
        glfwTerminate(); // GLFW 종료
        return -1; // 프로그램 종료
    }

    // 현재 컨텍스트를 생성한 윈도우로 설정
    glfwMakeContextCurrent(window);
    // 마우스 버튼 콜백 함수 등록
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // 마우스 커서 위치 콜백 함수 등록
    glfwSetCursorPosCallback(window, cursor_position_callback);

    glfwSwapInterval(1); // 수직 동기화 사용

    // 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // 이벤트 처리

        // 마우스 오른쪽 버튼이 눌려 있으면
        if (rightbtnDown)
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 빨간색 
        // 마우스 왼쪽 버튼이 눌려 있으면
        else if (leftbtnDown)
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 녹색 
        else
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검정색 

        glClear(GL_COLOR_BUFFER_BIT); // 버퍼를 지우고 새로운 프레임을 그림
        glfwSwapBuffers(window); // 프레임을 화면에 표시
    }

    // GLFW 종료
    glfwTerminate();
    return 0; // 프로그램 종료
}