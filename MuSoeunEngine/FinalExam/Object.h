#pragma once
#include <GLFW/glfw3.h>

void PixelToOpenGL(float FloorXpixel, float FloorYpixel);

// 기본 클래스
class Object {
public:
    float pojiX, pojiY, width, height;
    Object(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f)
        : pojiX(x), pojiY(y), width(w), height(h) {}

    virtual void OnCollisionEnter(Object& other) {}
};

// Star 클래스
class Star : public Object {
public:
    float size;

    Star() : Object(), size(0.0f) {}

    void OnCollisionEnter(Object& other) override {
        drawStar();
    }
    void drawStar() const;
};

// Player 클래스
class Player : public Object {
public:
    float velocityY = 0.0f; // y 축 속도
    bool isJumping = false; // 점프 상태

    Player() : Object(100.0f, 450.0f, 50.0f, 50.0f) {}

    void OnCollisionEnter(Object& other) override {
        drawPlayer();
    }
    void drawPlayer();
};

// ObstacleBlock 클래스
class ObstacleBlock : public Object {
public:
    float pojiX1 = 800.0f;
    float pojiX2 = 1600.0f;
    float pojiX3 = 2400.0f;
    float pojiX4 = 2500.0f;

    ObstacleBlock() : Object(0.0f, 0.0f, 50.0f, 100.0f) {}

    void OnCollisionEnter(Object& other) override {
        drawCac();
    }
    void drawCac();
};

// Floor 클래스
class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        drawFloor();
    }
    void drawFloor();
};

// PhysicsAABB 함수
int PhysicsAABB(const Object& A, const Object& B);

// 함수 구현
void PixelToOpenGL(float FloorXpixel, float FloorYpixel) {
    int Width = 800;
    int Height = 600;

    float FloorXgl = 2.0f * (FloorXpixel / Width) - 1.0f;
    float FloorYgl = 1.0f - 2.0f * (FloorYpixel / Height);

    glVertex2f(FloorXgl, FloorYgl);
}

void Player::drawPlayer() {
    // 검은색 테두리 사각형
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(pojiX - 3.0f, pojiY - 3.0f);
    PixelToOpenGL(pojiX - 3.0f, pojiY + height + 3.0f);
    PixelToOpenGL(pojiX + width + 3.0f, pojiY + height + 3.0f);
    PixelToOpenGL(pojiX + width + 3.0f, pojiY - 3.0f);
    glEnd();

    // 빨간색 사각형
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(pojiX, pojiY);
    PixelToOpenGL(pojiX, pojiY + height);
    PixelToOpenGL(pojiX + width, pojiY + height);
    PixelToOpenGL(pojiX + width, pojiY);
    glEnd();
}

void ObstacleBlock::drawCac() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(pojiX1, 400.0f);
    PixelToOpenGL(pojiX1, 500.0f);
    PixelToOpenGL(pojiX1 + width, 500.0f);
    PixelToOpenGL(pojiX1 + width, 400.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(pojiX2, 200.0f);
    PixelToOpenGL(pojiX2, 500.0f);
    PixelToOpenGL(pojiX2 + width, 500.0f);
    PixelToOpenGL(pojiX2 + width, 200.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(pojiX3, 400.0f);
    PixelToOpenGL(pojiX3, 500.0f);
    PixelToOpenGL(pojiX3 + width, 500.0f);
    PixelToOpenGL(pojiX3 + width, 400.0f);
    glEnd();

    glBegin(GL_POLYGON);
    PixelToOpenGL(pojiX4, 200.0f);
    PixelToOpenGL(pojiX4, 500.0f);
    PixelToOpenGL(pojiX4 + width, 500.0f);
    PixelToOpenGL(pojiX4 + width, 200.0f);
    glEnd();
}

void Floor::drawFloor() {
    glColor3f(1.0f, 0.78f, 0.05f);
    glBegin(GL_POLYGON);
    PixelToOpenGL(0.0f, 500.0f);
    PixelToOpenGL(0.0f, 600.0f);
    PixelToOpenGL(800.0f, 600.0f);
    PixelToOpenGL(800.0f, 500.0f);
    glEnd();
}

void Star::drawStar() const {
    float halfSize = size / 2.0f;
    float angle = 72.0f * 3.141592 / 180.0f; // 72 degrees in radians
    glColor3ub(255, 165, 0); // Orange color for star

    glBegin(GL_TRIANGLE_FAN);
    PixelToOpenGL(pojiX, pojiY); // Center of star

    for (int i = 0; i <= 5; ++i) {
        float xVertex = pojiX + halfSize * cos(i * 2 * angle);
        float yVertex = pojiY + halfSize * sin(i * 2 * angle);
        PixelToOpenGL(xVertex, yVertex);
    }

    glEnd();
}

int PhysicsAABB(const Object& A, const Object& B) {
    return (A.pojiX < B.pojiX + B.width &&
        A.pojiX + A.width > B.pojiX &&
        A.pojiY < B.pojiY + B.height &&
        A.pojiY + A.height > B.pojiY);
}