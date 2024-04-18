#pragma comment(lib, "Opengl32.lib")﻿

#include <GLFW/glfw3.h>
#include <iostream>
#include "Star.hpp"
#include "MSList.h"


float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}

MSList<MObject*> list;

int initialize()
{
	MObject* temp[300];
	for (int i = 0; i < 300; i++) {
		temp[i] = new Star();
		list.add(temp[i]);
		std::cout << "별의개수는!: " << list.get_size() << std::endl;
	}
	return 0;
}

int release()
{
	for (int i = 0; i < list.get_size(); i++) {
		delete list[i];
		std::cout << "별을 삭제!: " << i + 1 << std::endl;
	}
	list.clear();
	return 0;
}

int update()
{
	return 0;
}

int render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < list.get_size(); ++i) {
		MObject* obj = list[i];
		obj->render();
	}

	return 0;
}

int main(void)
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 768, "", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	initialize();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		render();
		glfwSwapBuffers(window);
	}

	release();
	glfwTerminate();
	return 0;
}