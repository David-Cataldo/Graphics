#pragma once

#include "PointLight.h"

class SpotLight :
    public PointLight
{
public:
    SpotLight();
    SpotLight(glm::vec3 ambientCol, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 pos, glm::vec3 dir, GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation,
        GLfloat positionLocation, GLfloat directionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation, GLfloat edgeLocation);

    void SetFlash(glm::vec3 pos, glm::vec3 dir);
    
    ~SpotLight();

private:
    glm::vec3 direction;

    GLfloat edge, procEdge;
};

