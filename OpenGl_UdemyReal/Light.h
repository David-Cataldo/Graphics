#pragma once

#include "ShadowMap.h"

class Light
{
public:
	Light();
	Light(GLuint shadowWidth, GLuint shadowHeight, 
		glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity);

	ShadowMap* GetShadowMap() { return shadowMap; }

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	glm::mat4 lightProj;

	ShadowMap* shadowMap;
};

