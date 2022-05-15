#pragma once

#include "CommonValues.h"

#include "Shader.h"
#include "Mesh.h"

class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocations);

	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();

private:
	Mesh* skyMesh;
	Shader* skyShader;

	GLuint textureID;
	GLuint uniformProjection, uniformView;
};

