#pragma once

#include "Light.h"

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 ambientCol, GLfloat aIntensity, glm::vec3 diffuseDir, GLfloat dIntensity);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

    ~DirectionalLight();

private:
    glm::vec3 direction;

};

