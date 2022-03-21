#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	~Mesh();

protected:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

};

