#include "MObject.h"
#include <GLFW/glfw3.h>
#include <random> 

class Star : public MObject
{
public:

    Star() : rd(), gen(rd()), dis(-1.0f, 1.0f), xPos(dis(gen)), yPos(dis(gen)), red(dis(gen)), green(dis(gen)), blue(dis(gen)) {}

    void update()
    {

    }

    void render()
    {

        glBegin(GL_POLYGON);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

        float xPos = dis(gen);
        float yPos = dis(gen);
        float red = dis(gen);
        float green = dis(gen);
        float blue = dis(gen);

        glColor3f(red, green, blue);// ·£´ý »ö


        glVertex2f((0.2f / scale) + xPos, (0.1f / scale) + yPos);
        glVertex2f(xPos + (0.8f / scale), yPos + (0.01f / scale));
        glVertex2f(xPos + (0.3f / scale), yPos + (-0.3f / scale));
        glVertex2f(xPos + (0.5f / scale), yPos + (-0.8f / scale));
        glVertex2f(xPos + (0.0f / scale), yPos + (-0.5f / scale));
        glVertex2f(xPos + (-0.5f / scale), yPos + (-0.8f / scale));
        glVertex2f(xPos + (-0.3f / scale), yPos + (-0.3f / scale));
        glVertex2f(xPos + (-0.8f / scale), yPos + (0.1f / scale));
        glVertex2f(xPos + (-0.2f / scale), yPos + (0.1f / scale));
        glVertex2f(xPos + (0.0f / scale), yPos + (0.8f / scale));
        glEnd();
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;
    float xPos;
    float yPos;
    float red;
    float green;
    float blue;
    int scale = 20;
};