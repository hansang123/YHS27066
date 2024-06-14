#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// 상수 정의
const float GRAVITY = 9.8f;
const float JUMP_VELOCITY_W = 3.5f;
const float JUMP_VELOCITY_E = 4.5f;
const float GROUND_Y = -0.8f;
const float SQUARE_SIZE = 0.25f;
const float OBSTACLE_SIZE = 0.2f;
const float OBSTACLE_SPEED = 2.0f;
const float OBSTACLE_SPAWN_INTERVAL = 2.0f;
const float BIRD_SIZE = 0.15f;
const float BIRD_SPEED = 1.5f;
const float BIRD_Y = 0.6f;
const float EGG_SIZE = 0.05f;
const float EGG_SPAWN_INTERVAL = 2.0f;
const float EGG_INITIAL_SPEED = 2.0f;

enum Direction { LEFT, RIGHT };

// 구조체 정의
struct Transform {
    float x, y;
};

struct Square {
    Transform transform;
    float velocityY;
};

struct Obstacle {
    Transform transform;
    float size;
};

struct Bird {
    Transform transform;
    float size;
    float speed;
    Direction direction;
};

struct Egg {
    Transform transform;
    float velocityX, velocityY;
};

// 전역 변수
Square player = { { -0.625f, 0.583f }, 0.0f };
std::vector<Obstacle> obstacles;
Bird bird = { { 0.0f, BIRD_Y }, BIRD_SIZE, BIRD_SPEED, Direction::RIGHT };
std::vector<Egg> eggs;
bool birdExists = false;
double lastObstacleSpawnTime = 0.0;
double lastEggSpawnTime = 0.0;
bool gameRunning = true;

// 콜백 함수
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_W || key == GLFW_KEY_E) && action == GLFW_PRESS && player.transform.y <= GROUND_Y + SQUARE_SIZE / 2 + 0.01f && gameRunning) {
        player.velocityY = (key == GLFW_KEY_W) ? JUMP_VELOCITY_W : JUMP_VELOCITY_E;
    }
}

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

// 장애물 생성 함수
void spawnObstacle() {
    Obstacle obstacle = { { 1.0f, GROUND_Y + OBSTACLE_SIZE / 2 }, OBSTACLE_SIZE };
    obstacles.push_back(obstacle);
}

// 새 생성 함수
void spawnBird() {
    bird = { { 0.0f, BIRD_Y }, BIRD_SIZE, BIRD_SPEED, Direction::RIGHT };
    birdExists = true;
}

// 알 생성 함수
void spawnEgg() {
    float velocityX = (rand() % 2 == 0) ? -EGG_INITIAL_SPEED : EGG_INITIAL_SPEED;
    Egg egg = { { bird.transform.x, bird.transform.y }, velocityX, 0.0f };
    eggs.push_back(egg);
}

// 충돌 검사 함수
bool checkCollision(const Square& player, const Obstacle& obstacle) {
    return (player.transform.x - SQUARE_SIZE / 2 < obstacle.transform.x + obstacle.size / 2 &&
        player.transform.x + SQUARE_SIZE / 2 > obstacle.transform.x - obstacle.size / 2 &&
        player.transform.y - SQUARE_SIZE / 2 < obstacle.transform.y + obstacle.size / 2 &&
        player.transform.y + SQUARE_SIZE / 2 > obstacle.transform.y - obstacle.size / 2);
}

bool checkBirdCollision(const Square& player, const Bird& bird) {
    return (player.transform.x - SQUARE_SIZE / 2 < bird.transform.x + bird.size / 2 &&
        player.transform.x + SQUARE_SIZE / 2 > bird.transform.x - bird.size / 2 &&
        player.transform.y - SQUARE_SIZE / 2 < bird.transform.y + bird.size / 2 &&
        player.transform.y + SQUARE_SIZE / 2 > bird.transform.y - bird.size / 2);
}

bool checkEggCollision(const Square& player, const Egg& egg) {
    return (player.transform.x - SQUARE_SIZE / 2 < egg.transform.x + EGG_SIZE / 2 &&
        player.transform.x + SQUARE_SIZE / 2 > egg.transform.x - EGG_SIZE / 2 &&
        player.transform.y - SQUARE_SIZE / 2 < egg.transform.y + EGG_SIZE / 2 &&
        player.transform.y + SQUARE_SIZE / 2 > egg.transform.y - EGG_SIZE / 2);
}

// 게임 업데이트 함수
void update(float deltaTime, double currentTime) {
    if (!gameRunning) return;

    // 플레이어 중력 적용 및 위치 업데이트
    player.velocityY -= GRAVITY * deltaTime;
    player.transform.y += player.velocityY * deltaTime;
    if (player.transform.y - SQUARE_SIZE / 2 < GROUND_Y) {
        player.transform.y = GROUND_Y + SQUARE_SIZE / 2;
        player.velocityY = 0;
    }

    // 장애물 위치 업데이트
    for (auto& obstacle : obstacles) {
        obstacle.transform.x -= OBSTACLE_SPEED * deltaTime;
    }

    // 새 위치 업데이트
    if (birdExists) {
        if (bird.direction == Direction::RIGHT) {
            bird.transform.x += bird.speed * deltaTime;
            if (bird.transform.x + bird.size / 2 > 1.0f) {
                bird.direction = Direction::LEFT;
            }
        }
        else {
            bird.transform.x -= bird.speed * deltaTime;
            if (bird.transform.x - bird.size / 2 < -1.0f) {
                bird.direction = Direction::RIGHT;
            }
        }
    }

    // 알 위치 업데이트 (포물선 운동)
    for (auto& egg : eggs) {
        egg.velocityY -= GRAVITY * deltaTime;
        egg.transform.x += egg.velocityX * deltaTime;
        egg.transform.y += egg.velocityY * deltaTime;
    }

    // 충돌 검사
    for (const auto& obstacle : obstacles) {
        if (checkCollision(player, obstacle)) {
            gameRunning = false;
            std::cout << "Game Over! Player collided with an obstacle." << std::endl;
            break;
        }
    }
    if (birdExists && checkBirdCollision(player, bird)) {
        gameRunning = false;
        std::cout << "Game Over! Player collided with a bird." << std::endl;
    }
    for (const auto& egg : eggs) {
        if (checkEggCollision(player, egg)) {
            gameRunning = false;
            std::cout << "Game Over! Player collided with an egg." << std::endl;
            break;
        }
    }

    // 화면 밖으로 나간 장애물 제거
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
        [](const Obstacle& obstacle) { return obstacle.transform.x + obstacle.size / 2 < -1.0f; }),
        obstacles.end());

    // 화면 밖으로 나간 알 제거
    eggs.erase(std::remove_if(eggs.begin(), eggs.end(),
        [](const Egg& egg) { return egg.transform.y + EGG_SIZE / 2 < GROUND_Y - 1.0f; }),
        eggs.end());

    // 새로운 장애물 생성
    if (currentTime - lastObstacleSpawnTime > OBSTACLE_SPAWN_INTERVAL) {
        spawnObstacle();
        lastObstacleSpawnTime = currentTime;
    }

    // 새로운 새 생성 (한 번만)
    if (!birdExists) {
        spawnBird();
    }

    // 새로운 알 생성
    if (birdExists && currentTime - lastEggSpawnTime > EGG_SPAWN_INTERVAL) {
        spawnEgg();
        lastEggSpawnTime = currentTime;
    }
}

// 메인 함수
int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Dinosaur Run", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    std::srand(static_cast<unsigned int>(std::time(0)));

    while (!glfwWindowShouldClose(window)) {
        static double previousTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        update(deltaTime, currentTime);

        // 화면 그리기
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 하얀색 배경
        glClear(GL_COLOR_BUFFER_BIT);

        // 바닥 그리기
        glColor3f(0.0f, 1.0f, 0.0f); // 초록색
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, GROUND_Y);
        glVertex2f(1.0f, GROUND_Y);
        glVertex2f(1.0f, GROUND_Y - 0.2f);
        glVertex2f(-1.0f, GROUND_Y - 0.2f);
        glEnd();

        // 플레이어 사각형 그리기 (빨간색)
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(player.transform.x - SQUARE_SIZE / 2, player.transform.y - SQUARE_SIZE / 2);
        glVertex2f(player.transform.x + SQUARE_SIZE / 2, player.transform.y - SQUARE_SIZE / 2);
        glVertex2f(player.transform.x + SQUARE_SIZE / 2, player.transform.y + SQUARE_SIZE / 2);
        glVertex2f(player.transform.x - SQUARE_SIZE / 2, player.transform.y + SQUARE_SIZE / 2);
        glEnd();

        // 장애물 그리기 (파란색)
        glColor3f(0.0f, 0.0f, 1.0f);
        for (const auto& obstacle : obstacles) {
            glBegin(GL_QUADS);
            glVertex2f(obstacle.transform.x - obstacle.size / 2, obstacle.transform.y - obstacle.size / 2);
            glVertex2f(obstacle.transform.x + obstacle.size / 2, obstacle.transform.y - obstacle.size / 2);
            glVertex2f(obstacle.transform.x + obstacle.size / 2, obstacle.transform.y + obstacle.size / 2);
            glVertex2f(obstacle.transform.x - obstacle.size / 2, obstacle.transform.y + obstacle.size / 2);
            glEnd();
        }

        // 새 그리기 (노란색)
        if (birdExists) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(bird.transform.x - bird.size / 2, bird.transform.y - bird.size / 2);
            glVertex2f(bird.transform.x + bird.size / 2, bird.transform.y - bird.size / 2);
            glVertex2f(bird.transform.x + bird.size / 2, bird.transform.y + bird.size / 2);
            glVertex2f(bird.transform.x - bird.size / 2, bird.transform.y + bird.size / 2);
            glEnd();
        }

        // 알 그리기 (검정색)
        glColor3f(0.0f, 0.0f, 0.0f);
        for (const auto& egg : eggs) {
            glBegin(GL_QUADS);
            glVertex2f(egg.transform.x - EGG_SIZE / 2, egg.transform.y - EGG_SIZE / 2);
            glVertex2f(egg.transform.x + EGG_SIZE / 2, egg.transform.y - EGG_SIZE / 2);
            glVertex2f(egg.transform.x + EGG_SIZE / 2, egg.transform.y + EGG_SIZE / 2);
            glVertex2f(egg.transform.x - EGG_SIZE / 2, egg.transform.y + EGG_SIZE / 2);
            glEnd();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // GLFW 자원 해제
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}