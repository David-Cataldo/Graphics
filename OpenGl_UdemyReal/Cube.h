#pragma once

#include "Mesh.h"
#include <iostream>


class Cube
{
public:
	Cube(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 0.0f));

	void RenderCube();
	void ScaleCube();
	void TranslateCube();
	void SelectCube(GLfloat x, GLfloat y);

	~Cube();

private:
	glm::vec3 pos;
	glm::vec3 scale;

	GLfloat vertices[24];
	unsigned int indices[36];

	Mesh* mainMesh;

	bool isSelected();
};

