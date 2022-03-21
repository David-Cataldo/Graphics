#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MyWindow
{
public:
	MyWindow();
	MyWindow(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLfloat GetBufferWidth() { return bufferWidth; }
	GLfloat GetBufferHeight() { return bufferHeight; }

	GLfloat GetWidth() { return width; }
	GLfloat GetHeight() { return height; }

	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }
	
	bool* GetKeys() { return keys; }
	bool IsLeftClicking() { return glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_LEFT); }
	GLfloat GetXChange();
	GLfloat GetYChange();
	GLfloat GetMouseX() { return lastX; }
	GLfloat GetMouseY() { return lastY; }

	void UpdateSize();
	void SwapBuffers() { glfwSwapBuffers(mainWindow); }

	~MyWindow();
	
private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

 