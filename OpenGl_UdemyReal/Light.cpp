#include "pch.h"
#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity)
{
	color = clamp(ambientCol, 0.0f, 1.0f);
	ambientIntensity = aIntensity;

	diffuseIntensity = dIntensity;
}

Light::~Light()
{

}