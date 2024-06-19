#pragma comment(lib, "OpenGL32.lib")
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.h"
#include "Transform.h"

using namespace std::chrono;

// 전역 변수로 Player 객체 선언
Player player;
bool isCollision = false; // 충돌 여부 확인 변수

// 시간 측정을 위한 변수
high_resolution_clock::time_point lastTime;

// Error callback 함수
void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s", description);
}

// Initialize 함수
int Initialize() {
    glClearColor(0.0f, 0.11f, 0.25f, 1.0f);
    lastTime = high_resolution_clock::now();
    return 0;
}

// Key callback 함수
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !player.isJumping) {
        player.velocityY = 1000.0f; // 점프 시작 (5m = 500픽셀)
        player.isJumping = true;
    }
}

// Physics 함수
int Physics() {
    return 0;
}

// Update 함수
int Update(ObstacleBlock& obstacle, Player& player, Star stars[], int starCount, float deltaTime) {
    float gravity = 9.8f * 100; // 중력 가속도 (픽셀 단위)

    if (isCollision) return 0;

    // 플레이어 위치 업데이트
    applyGravityAndJump(player.pojiY, player.velocityY, player.isJumping, gravity, deltaTime);

    // 적 위치 업데이트
    float obstacleSpeed = 300.0f; // 적 이동 속도
    updateObstaclePosition(obstacle.pojiX1, obstacleSpeed, deltaTime);
    updateObstaclePosition(obstacle.pojiX2, obstacleSpeed, deltaTime);
    updateObstaclePosition(obstacle.pojiX3, obstacleSpeed, deltaTime);
    updateObstaclePosition(obstacle.pojiX4, obstacleSpeed, deltaTime);
    resetObstaclePositions(obstacle, -10.0f);

    // 별 위치 업데이트
    float starSpeed = 100.0f; // 별 이동 속도
    for (int i = 0; i < starCount; ++i) {
        updateStarPosition(stars[i].pojiX, starSpeed, deltaTime);
        resetStarPosition(stars[i].pojiX, -10.0f, 810.0f);
    }

    // 충돌 검사
    if (PhysicsAABB(player, Object(obstacle.pojiX1, 400.0f, 50.0f, 100.0f)) ||
        PhysicsAABB(player, Object(obstacle.pojiX2, 200.0f, 50.0f, 300.0f)) ||
        PhysicsAABB(player, Object(obstacle.pojiX3, 400.0f, 50.0f, 100.0f)) ||
        PhysicsAABB(player, Object(obstacle.pojiX4, 200.0f, 50.0f, 300.0f))) {
        isCollision = true;
    }

    return 0;
}

// Render 함수
int Render(ObstacleBlock& obstacle, Player& player, const Star stars[], int starCount) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < starCount; ++i) {
        stars[i].drawStar();
    }
    Object other;
    player.OnCollisionEnter(other);
    Floor floor;
    floor.OnCollisionEnter(other);
    obstacle.OnCollisionEnter(other);
    return 0;
}

// main 함수
int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Dino Run Copy Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    ObstacleBlock obstacle;

    // 5개의 별 생성
    const int starCount = 5;
    Star stars[starCount];
    for (int i = 0; i < starCount; ++i) {
        stars[i].pojiX = randomFloat(0.0f, 500.0f);
        stars[i].pojiY = randomFloat(0.0f, 300.0f);
        stars[i].size = randomFloat(50.0f, 100.0f); // 크기를 픽셀 단위로 지정
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // deltaTime 계산
        high_resolution_clock::time_point currentTime = high_resolution_clock::now();
        duration<float> elapsedTime = duration_cast<duration<float>>(currentTime - lastTime);
        float deltaTime = elapsedTime.count();
        lastTime = currentTime;

        Physics();
        Update(obstacle, player, stars, starCount, deltaTime);
        Render(obstacle, player, stars, starCount);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}