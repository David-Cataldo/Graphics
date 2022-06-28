#include "Block.h"
#include <iostream>

Texture Block::s_allTextures = Texture("Textures/dirt.png");

Block::Block()
{
	m_mesh = Mesh();
	m_modelMatrix = glm::mat4(1.0f);
}

Block::Block(TexCoords t, glm::vec3 pos) : m_modelMatrix(glm::mat4(1.0f))
{
	m_mesh = Mesh();
	m_modelMatrix = glm::translate(m_modelMatrix, pos);


	//GLfloat vertices[] = {
	//	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,/*t.u/16.0f, t.v/16.0f,		*/	//0
	//	 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,/*(t.u+1)/16.0f, t.v/16.0f,	*/	//1
	//	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,/*t.u/16.0f, (t.v+1)/16.0f,	*/	//2
	//	 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,/*(t.u+1)/16.0f, (t.v+1)/16.0f,*/ //3
	//	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,/*t.u/16.0f, t.v/16.0f,		*/	//4
	//	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,/*(t.u+1)/16.0f, t.v/16.0f,	*/	//5
	//	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,/*t.u/16.0f, (t.v+1)/16.0f,	*/	//6
	//	 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,/*(t.u+1)/16.0f, (t.v+1)/16.0f */ //7
	//};
	//
	//unsigned int indices[] = {
	//	//Top
	//	2, 6, 7,
	//	2, 3, 7,
	//
	//	//Bottom
	//	0, 4, 5,
	//	0, 1, 5,
	//
	//	//Left
	//	0, 2, 6,
	//	0, 4, 6,
	//
	//	//Right
	//	1, 3, 7,
	//	1, 5, 7,
	//
	//	//Front
	//	0, 2, 3,
	//	0, 1, 3,
	//
	//	//Back
	//	4, 6, 7,
	//	4, 5, 7
	//};

	GLfloat vertices[] = {
		5.0f, 5.0f, 5.0f, 1.0f, 0.0f,
		-5.0f, -5.0f, 5.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -3.0f, 4.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		3, 2, 0,
		0, 2, 1,
		1, 2, 3
	};
	

    m_mesh.CreateMesh(vertices, indices, 20, 12);
}

void Block::Draw(GLuint modelLocation)
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
	s_allTextures.UseTexture();
    m_mesh.RenderMesh();
}