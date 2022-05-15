#pragma once

class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	inline GLfloat* GetVerts() { return verts; }
	inline unsigned int* GetIndices() { return indices; }
	inline unsigned int GetNumOfVerts() { return numOfVerts; }
	inline unsigned int GetNumOfInds() { return numOfIndices; }

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	GLfloat* verts;
	unsigned int* indices;
	unsigned int numOfVerts;
	unsigned int numOfIndices;
};

