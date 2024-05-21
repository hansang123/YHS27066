#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>

const double PI = 3.14159265358979323846;

// 원 그리기 함수
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// 별 그리기 함수
void drawStar(double centerX, double centerY, double radius, double angle) {
    double radians = angle * PI / 180.0;
    double cosAngle = cos(radians);
    double sinAngle = sin(radians);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // 별의 중심
    for (int i = 0; i <= 5; ++i) {
        double angle = i * (4.0 * PI / 5.0) + PI / 2.0; // 별의 외곽 점 각도
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        double rotatedX = x * cosAngle - y * sinAngle;
        double rotatedY = x * sinAngle + y * cosAngle;
        glVertex2f(centerX + rotatedX, centerY + rotatedY); // 외곽 점
        angle += (2.0 * PI / 5.0); // 내곽 점 각도
        x = (radius / 2.5) * cos(angle);
        y = (radius / 2.5) * sin(angle);
        rotatedX = x * cosAngle - y * sinAngle;
        rotatedY = x * sinAngle + y * cosAngle;
        glVertex2f(centerX + rotatedX, centerY + rotatedY); // 내곽 점
    }
    glEnd();
}

// 사각형 그리기 함수
void drawSquare(float cx, float cy, float size, double angle) {
    float halfSize = size / 2;
    double radians = angle * PI / 180.0;
    double cosAngle = cos(radians);
    double sinAngle = sin(radians);

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        float x = (i < 2) ? -halfSize : halfSize;
        float y = (i % 3 == 0) ? -halfSize : halfSize;
        double rotatedX = x * cosAngle - y * sinAngle;
        double rotatedY = x * sinAngle + y * cosAngle;
        glVertex2f(cx + rotatedX, cy + rotatedY);
    }
    glEnd();

    // 사각형의 아웃라인 그리기
    glColor3ub(0, 0, 0); // 검은색 아웃라인
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; ++i) {
        float x = (i < 2) ? -halfSize : halfSize;
        float y = (i % 3 == 0) ? -halfSize : halfSize;
        double rotatedX = x * cosAngle - y * sinAngle;
        double rotatedY = x * sinAngle + y * cosAngle;
        glVertex2f(cx + rotatedX, cy + rotatedY);
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawRotatedEllipse(float cx, float cy, float rx, float ry, float angle, int num_segments) {
    double radians = angle * PI / 180.0;
    double cosAngle = cos(radians);
    double sinAngle = sin(radians);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // 중심
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        float rotatedX = x * cosAngle - y * sinAngle;
        float rotatedY = x * sinAngle + y * cosAngle;
        glVertex2f(rotatedX + cx, rotatedY + cy);
    }
    glEnd();
}

int main() {
    // GLFW 초기화
    if (!glfwInit())
        return -1;

    // 윈도우 모드 윈도우 생성 및 OpenGL 컨텍스트 생성
    GLFWwindow* window = glfwCreateWindow(800, 800, "Planetary Motion", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 현재 컨텍스트로 윈도우의 컨텍스트 설정
    glfwMakeContextCurrent(window);

    // 수직 동기화 설정
    glfwSwapInterval(1);

    // 사용자가 윈도우를 닫을 때까지 루프
    while (!glfwWindowShouldClose(window)) {
        // 버퍼 초기화
        glClear(GL_COLOR_BUFFER_BIT);

        // 윈도우 크기 가져오기
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // 뷰포트 설정
        glViewport(0, 0, width, height);

        // 투영 행렬 설정
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);

        // 모델뷰 행렬 설정
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // 중심 좌표
        double centerX = width / 2.0;
        double centerY = height / 2.0;

        // 중심에서 지구까지의 거리
        double earthOrbitRadius = 300;

        // 지구에서 달까지의 거리
        double moonOrbitRadius = 60;

        // 시간 기반 회전 각도 계산
        double time = glfwGetTime();
        double sunRotation = fmod(time / 30.0 * 360.0, 360.0); // 30초 주기로 태양 자전
        double earthOrbitRotation = fmod(time / 60.0 * 360.0, 360.0); // 1분 주기로 지구가 태양 주위를 공전
        double earthRotation = fmod(time / 10.0 * 360.0, 360.0); // 10초 주기로 지구 자전
        double moonOrbitRotation = fmod(time / 3.0 * 360.0, 360.0); // 3초 주기로 달이 지구 주위를 공전
        double moonRotation = fmod(time / 3.0 * 360.0, 360.0); // 3초 주기로 달 자전

        // 태양 그리기
        double sunX = centerX;
        double sunY = centerY;

        glColor3ub(255, 217, 102); // 큰 원 색상
        drawCircle(sunX, sunY, 100.0, 360); // 큰 원

        // 태양의 중간 원 그리기 (왼쪽 상단으로 이동)
        double middleCircleX = sunX - 30.0 * cos(sunRotation * PI / 180.0);
        double middleCircleY = sunY - 30.0 * sin(sunRotation * PI / 180.0);
        glColor3ub(255, 230, 153); // 중간 원 색상
        drawCircle(middleCircleX, middleCircleY, 35.0, 360); // 중간 원

        // 태양의 작은 원 그리기 (오른쪽 하단으로 이동 및 축소 후 회전)
        double smallCircleX = sunX + 70.0 * cos(sunRotation * PI / 180.0);
        double smallCircleY = sunY + 50.0 * sin(sunRotation * PI / 180.0); // 아래로 이동
        glColor3ub(255, 192, 0); // 작은 원 색상
        drawRotatedEllipse(smallCircleX, smallCircleY, 25.0, 6.25, 45.0, 360); // 작은 원을 세로로 축소하고 회전

        // 태양의 아웃라인 그리기
        glColor3ub(214, 130, 55); // 아웃라인 색상
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i++) {
            double theta = i * PI / 180.0;
            glVertex2f(sunX + 100.0 * cos(theta), sunY + 100.0 * sin(theta));
        }
        glEnd();

        // 지구 그리기
        double earthX = centerX + earthOrbitRadius * cos(earthOrbitRotation * PI / 180.0);
        double earthY = centerY + earthOrbitRadius * sin(earthOrbitRotation * PI / 180.0);
        glColor3f(0.0, 0.0, 1.0);
        drawSquare(earthX, earthY, 50.0, -earthRotation); // 시계 반대 방향으로 자전

        // 달 그리기
        double moonX = earthX + moonOrbitRadius * cos(moonOrbitRotation * PI / 180.0);
        double moonY = earthY + moonOrbitRadius * sin(moonOrbitRotation * PI / 180.0);
        glColor3ub(255, 242, 0); // 달 색상
        drawStar(moonX, moonY, 20.0, moonRotation);

        // 프론트와 백 버퍼 교환
        glfwSwapBuffers(window);

        // 이벤트 처리
        glfwPollEvents();
    }

    // GLFW 종료
    glfwTerminate();

    return 0;
}