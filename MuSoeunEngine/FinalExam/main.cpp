#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.h"  // Object.h 헤더 파일 포함

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

int Physics()
{
    return 0;
}

int Initialize()
{
    return 0;
}

int Update()
{
    return 0;
}

void drawGround(float ground_height, float ground_color_r, float ground_color_g, float ground_color_b)
{
    // 지면 그리기
    glColor3f(ground_color_r, ground_color_g, ground_color_b);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, ground_height); // 왼쪽 아래
    glVertex2f(800.0f, ground_height); // 오른쪽 아래
    glVertex2f(800.0f, 0.0f); // 오른쪽 위
    glVertex2f(0.0f, 0.0f); // 왼쪽 위
    glEnd();
}

void drawPlayer(float player_x, float player_y, float player_size, float player_color_r, float player_color_g, float player_color_b, float player_border_thickness)
{
    // 플레이어 그리기 (내부)
    glColor3f(player_color_r, player_color_g, player_color_b);
    glBegin(GL_QUADS);
    glVertex2f(player_x - player_size / 2.0f, player_y - player_size / 2.0f); // 왼쪽 아래
    glVertex2f(player_x + player_size / 2.0f, player_y - player_size / 2.0f); // 오른쪽 아래
    glVertex2f(player_x + player_size / 2.0f, player_y + player_size / 2.0f); // 오른쪽 위
    glVertex2f(player_x - player_size / 2.0f, player_y + player_size / 2.0f); // 왼쪽 위
    glEnd();

    // 플레이어 테두리 그리기
    glColor3f(0.0f, 0.0f, 0.0f); // 검은색 테두리
    glLineWidth(player_border_thickness);
    glBegin(GL_LINE_LOOP);
    glVertex2f(player_x - player_size / 2.0f, player_y - player_size / 2.0f); // 왼쪽 아래
    glVertex2f(player_x + player_size / 2.0f, player_y - player_size / 2.0f); // 오른쪽 아래
    glVertex2f(player_x + player_size / 2.0f, player_y + player_size / 2.0f); // 오른쪽 위
    glVertex2f(player_x - player_size / 2.0f, player_y + player_size / 2.0f); // 왼쪽 위
    glEnd();
}

void drawObstacles(float obstacle1_x, float obstacle2_x, float obstacle_y, float obstacle_width, float obstacle_low_height, float obstacle_high_height, float obstacle_color_r, float obstacle_color_g, float obstacle_color_b)
{
    // 장애물 그리기 (낮은 장애물)
    glColor3f(obstacle_color_r, obstacle_color_g, obstacle_color_b);
    glBegin(GL_QUADS);
    glVertex2f(obstacle1_x - obstacle_width / 2.0f, obstacle_y); // 왼쪽 아래
    glVertex2f(obstacle1_x + obstacle_width / 2.0f, obstacle_y); // 오른쪽 아래
    glVertex2f(obstacle1_x + obstacle_width / 2.0f, obstacle_y + obstacle_low_height); // 오른쪽 위
    glVertex2f(obstacle1_x - obstacle_width / 2.0f, obstacle_y + obstacle_low_height); // 왼쪽 위
    glEnd();

    // 장애물 그리기 (높은 장애물)
    glBegin(GL_QUADS);
    glVertex2f(obstacle2_x - obstacle_width / 2.0f, obstacle_y); // 왼쪽 아래
    glVertex2f(obstacle2_x + obstacle_width / 2.0f, obstacle_y); // 오른쪽 아래
    glVertex2f(obstacle2_x + obstacle_width / 2.0f, obstacle_y + obstacle_high_height); // 오른쪽 위
    glVertex2f(obstacle2_x - obstacle_width / 2.0f, obstacle_y + obstacle_high_height); // 왼쪽 위
    glEnd();
}

void Render(float ground_height, float ground_color_r, float ground_color_g, float ground_color_b,
    float player_x, float player_y, float player_size, float player_color_r, float player_color_g, float player_color_b, float player_border_thickness,
    float obstacle1_x, float obstacle2_x, float obstacle_y, float obstacle_width, float obstacle_low_height, float obstacle_high_height, float obstacle_color_r, float obstacle_color_g, float obstacle_color_b)
{
    drawGround(ground_height, ground_color_r, ground_color_g, ground_color_b);
    drawPlayer(player_x, player_y, player_size, player_color_r, player_color_g, player_color_b, player_border_thickness);
    drawObstacles(obstacle1_x, obstacle2_x, obstacle_y, obstacle_width, obstacle_low_height, obstacle_high_height, obstacle_color_r, obstacle_color_g, obstacle_color_b);
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // glfw라이브러리 초기화
    if (!glfwInit())
        return -1;

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    // 배경색 설정
    const float bg_color_r = 0.0f / 255.0f;
    const float bg_color_g = 30.0f / 255.0f;
    const float bg_color_b = 100.0f / 255.0f;

    // 지면색 설정
    const float ground_color_r = 255.0f / 255.0f;
    const float ground_color_g = 200.0f / 255.0f;
    const float ground_color_b = 15.0f / 255.0f;

    // 플레이어 설정
    const float player_size = 50.0f; // 플레이어 크기 (50cm)
    const float player_border_thickness = 3.0f; // 테두리 두께 (3cm)
    const float player_color_r = 255.0f / 255.0f;
    const float player_color_g = 0.0f / 255.0f;
    const float player_color_b = 0.0f / 255.0f;

    // 지면 높이 (화면 바닥으로부터 100cm = 100픽셀)
    const float ground_height = 100.0f;

    // 플레이어 초기 위치 (지면 위)
    float player_x = 100.0f;
    float player_y = ground_height + player_size / 2.0f;

    // 장애물 설정
    const float obstacle_width = 50.0f; // 장애물 너비 (50cm)
    const float obstacle_low_height = 100.0f; // 낮은 장애물 높이 (100cm)
    const float obstacle_high_height = 300.0f; // 높은 장애물 높이 (300cm)
    const float obstacle_color_r = 0.0f / 255.0f;
    const float obstacle_color_g = 255.0f / 255.0f;
    const float obstacle_color_b = 0.0f / 255.0f;

    // 장애물 위치 (지면 위)
    float obstacle1_x = 300.0f; // 낮은 장애물 위치
    float obstacle2_x = 500.0f; // 높은 장애물 위치
    float obstacle_y = ground_height;

    // 뷰포트 설정 (여기서 1픽셀을 1cm로 간주)
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    Initialize();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Physics();
        Update();

        // 배경색 설정
        glClearColor(bg_color_r, bg_color_g, bg_color_b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Render(ground_height, ground_color_r, ground_color_g, ground_color_b,
            player_x, player_y, player_size, player_color_r, player_color_g, player_color_b, player_border_thickness,
            obstacle1_x, obstacle2_x, obstacle_y, obstacle_width, obstacle_low_height, obstacle_high_height, obstacle_color_r, obstacle_color_g, obstacle_color_b);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}