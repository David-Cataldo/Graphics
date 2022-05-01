#pragma once

#include "Light.h"

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(GLuint shadowWidth, GLuint shadowHeight, glm::vec3 ambientCol, GLfloat aIntensity, glm::vec3 diffuseDir, GLfloat dIntensity);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

    glm::mat4 CalculateLightTransform();

    ~DirectionalLight();

private:
    glm::vec3 direction;

};

