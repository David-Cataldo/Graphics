#include "pch.h"
#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far, 
	glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity, 
	glm::vec3 pos, glm::vec3 dir, GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg)
	: PointLight(shadowWidth, shadowHeight, near, far, ambientCol, aIntensity, dIntensity, pos, con, lin, exp)
{
	direction = glm::normalize(dir);
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}


void SpotLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat positionLocation, GLfloat directionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation, GLfloat edgeLocation)
{
	if(isOn)
	{
		glUniform1f(ambientIntensityLocation, ambientIntensity);
		glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	}
	else
	{
		glUniform1f(ambientIntensityLocation, 0.0f);
		glUniform1f(diffuseIntensityLocation, 0.0f);
	}
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
	
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}


SpotLight::~SpotLight()
{

}