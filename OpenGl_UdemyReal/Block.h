#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Mesh.h"
#include "Texture.h"

class Block
{
public:
	Block();
	Block(TexCoords t, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));

	void Draw(GLuint modelLocation);

public:
	static Texture s_allTextures;

public:
	Mesh m_mesh;
	glm::mat4 m_modelMatrix;
};

