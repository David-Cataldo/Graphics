#include "pch.h"
#include "PointLight.h"

PointLight::PointLight() : Light()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;

}

PointLight::PointLight(glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 pos, GLfloat con, GLfloat lin, GLfloat exp) : Light(1024, 1024, ambientCol, aIntensity, dIntensity)
{
    position = pos;
    constant = con;
    linear = lin;
    exponent = exp;
}

void PointLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation,
    GLfloat positionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);
}

PointLight::~PointLight()
{

}