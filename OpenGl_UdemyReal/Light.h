#pragma once

class Light
{
public:
	Light();
	Light(glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

