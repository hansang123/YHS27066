#pragma once

#include "Object.h"

namespace Transform
{
    struct Vertex
    {
        float x;
        float y;
    };

    struct Vector
    {
        float x_meter;
        float y_meter;
    };

    Vertex MoveVertex(Vertex point, Vector meter);
    Vertex RotateVertex(Vertex point, float angle_degree);
    Vertex ScaleVertex(Vertex point, Vector meter);
};

void updateObstaclePosition(float& x, float speed, float deltaTime);
void updateStarPosition(float& x, float speed, float deltaTime);
void resetObstaclePositions(ObstacleBlock& obstacle, float resetThreshold);
void resetStarPosition(float& x, float resetThreshold, float newX);
void applyGravityAndJump(float& pojiY, float& velocityY, bool& isJumping, float gravity, float deltaTime);
float randomFloat(float min, float max);

// ÇÔ¼ö ±¸Çö

// Simple pseudo-random number generator
unsigned int seed = 0;

float pseudoRandom() {
    seed = (8253729 * seed + 2396403); // Example constants
    return seed * (1.0f / 4294967296.0f);
}

float randomFloat(float min, float max) {
    return min + (max - min) * pseudoRandom();
}

void updateObstaclePosition(float& x, float speed, float deltaTime) {
    x -= speed * deltaTime;
}

void updateStarPosition(float& x, float speed, float deltaTime) {
    x -= speed * deltaTime;
}

void resetObstaclePositions(ObstacleBlock& obstacle, float resetThreshold) {
    if (obstacle.pojiX4 < resetThreshold) {
        obstacle.pojiX1 = 800.0f;
        obstacle.pojiX2 = 1600.0f;
        obstacle.pojiX3 = 2400.0f;
        obstacle.pojiX4 = 2500.0f;
    }
}

void resetStarPosition(float& x, float resetThreshold, float newX) {
    if (x < resetThreshold) {
        x = newX;
    }
}

void applyGravityAndJump(float& pojiY, float& velocityY, bool& isJumping, float gravity, float deltaTime) {
    if (isJumping) {
        velocityY -= gravity * deltaTime;
        pojiY -= velocityY * deltaTime;  // Á¡ÇÁ ½Ã yÁÂÇ¥¸¦ ³·Ãã

        if (pojiY >= 450.0f) { // ¹Ù´Ú À§Ä¡·Î °íÁ¤
            pojiY = 450.0f;
            velocityY = 0.0f;
            isJumping = false;
        }
    }
}