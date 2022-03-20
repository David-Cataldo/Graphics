#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 startUp = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat startYaw = -90.0f, GLfloat startPitch = 0.0f, GLfloat moveSpeed = 5.0f, GLfloat rotSpeed = 0.2f);

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange, bool isLeftClicking);
	
	glm::mat4 CalculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat turnSpeed;

	void Update();
};

