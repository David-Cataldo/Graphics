#pragma once

#include "Light.h"
#include "OmniShadowMap.h"

class PointLight :
    public Light
{
public:
    PointLight();
    PointLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far,
        glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity, 
        glm::vec3 pos, GLfloat con, GLfloat lin, GLfloat exp);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, 
        GLfloat positionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

    std::vector<glm::mat4> CalculateLightTransform();

    GLfloat GetFarPlane() { return farPlane; }
    glm::vec3 GetPosition() { return position; }

    ~PointLight();

protected:
    glm::vec3 position;

    GLfloat constant, linear, exponent;

    GLfloat farPlane;
};

