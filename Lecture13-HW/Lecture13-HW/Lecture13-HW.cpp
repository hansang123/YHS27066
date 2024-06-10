#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

const float gravity = 9.8f;
const float jumpVelocity = 5.0f;
const float groundY = -0.8f; 
const float squareSize = 0.5f;

struct Square {
    float x, y;
    float velocityY;
};


Square player = { -0.625f, 0.583f, 0.0f }; 

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && player.y <= groundY + squareSize / 2 + 0.01f)
    {
        player.velocityY = jumpVelocity;  // Jump when space is pressed
    }
}

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void render()
{
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ground
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, groundY);
    glVertex2f(1.0f, groundY);
    glVertex2f(1.0f, groundY - 0.2f); 
    glVertex2f(-1.0f, groundY - 0.2f);
    glEnd();

    // Draw player square (red)
    glColor3f(1.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2f(player.x - squareSize / 2 + 0.625, player.y - squareSize / 2);
    glVertex2f(player.x + squareSize / 2 + 0.625, player.y - squareSize / 2);
    glVertex2f(player.x + squareSize / 2 + 0.625, player.y + squareSize / 2);
    glVertex2f(player.x - squareSize / 2 + 0.625, player.y + squareSize / 2);
    glEnd();
}

void update(float deltaTime)
{
    
    player.velocityY -= gravity * deltaTime;
    
    player.y += player.velocityY * deltaTime;

   
    if (player.y - squareSize / 2 < groundY)
    {
        
        player.y = groundY + squareSize / 2;
        
        player.velocityY = 0;
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Dinosaur Run", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
       
        static double previousTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        
        update(deltaTime);

       
        glLoadIdentity();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}