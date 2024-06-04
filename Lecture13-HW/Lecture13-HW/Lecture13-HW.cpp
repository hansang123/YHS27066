#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>

const int WIDTH = 1920;
const int HEIGHT = 1080;

// 네모의 초기 위치 및 속도
float rectX = -0.7f;
float rectY = -0.5f;
float velocityY = 0.0f;
const float GRAVITY = -0.0004f; // 중력 가속도 
const float JUMP_VELOCITY = 0.016f; // 점프 초기 속도
bool isJumping = false;
double lastTime = 0.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping) {
        velocityY = JUMP_VELOCITY;
        isJumping = true;
    }
}

void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Jumping Rectangle", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // 배경을 흰색으로 초기화
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // 바닥을 그린다 (고정된 사각형)
        glColor3f(0.0f, 1.0f, 0.0f); // 초록색
        drawRectangle(-1.0f, -1.0f, 3.0f, 0.5f);

        // 점프하는 네모를 그린다
        glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
        drawRectangle(rectX, rectY, 0.1f, 0.13f);

        // 점프 로직
        if (isJumping) {
            rectY += velocityY * deltaTime * 100;
            velocityY += GRAVITY * deltaTime * 100; // 중력 효과

            if (rectY <= -0.5f) { // 바닥에 닿으면
                rectY = -0.5f;
                isJumping = false;
                velocityY = 0.0f;
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}