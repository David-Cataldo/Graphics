#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat moveSpeed, GLfloat rotSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = moveSpeed;
	turnSpeed = rotSpeed;

	Update();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{

	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		position += front * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		position += right * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		position -= right * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		position -= front * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_LEFT_SHIFT])
	{
		position -= worldUp * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_SPACE])
	{
		position += worldUp * movementSpeed * deltaTime;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange, bool isLeftClicking)
{
	if (!isLeftClicking)
	{
		return;
	}
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, worldUp);
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{

}
