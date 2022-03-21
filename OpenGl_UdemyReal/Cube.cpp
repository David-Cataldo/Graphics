#include "Cube.h"

Cube::Cube(glm::vec3 startPos)
{
	pos = startPos;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	mainMesh = new Mesh();
	
	// set vertex positions based on world position of cube
	vertices[0] = scale.x / 2; vertices[1] = scale.y / 2; vertices[2] = scale.z / 2;
	vertices[3] = scale.x / 2; vertices[4] = scale.y / 2; vertices[5] = -scale.z / 2;
	vertices[6] = -scale.x / 2; vertices[7] = scale.y / 2; vertices[8] = -scale.z / 2;
	vertices[9] = -scale.x / 2; vertices[10] = scale.y / 2; vertices[11] = scale.z / 2;

	vertices[12] = scale.x / 2; vertices[13] = -scale.y / 2; vertices[14] = scale.z / 2;
	vertices[15] = scale.x / 2; vertices[16] = -scale.y / 2; vertices[17] = -scale.z / 2;
	vertices[18] = -scale.x / 2; vertices[19] = -scale.y / 2; vertices[20] = -scale.z / 2;
	vertices[21] = -scale.x / 2; vertices[22] = -scale.y / 2; vertices[23] = scale.z / 2;

	std::cout << scale.x / 2 << " " << scale.y / 2 << " " << scale.z / 2 << std::endl;

	// draw faces 
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 3; indices[5] = 0;

	indices[6] = 0; indices[7] = 4; indices[8] = 7;
	indices[9] = 7; indices[10] = 3; indices[11] = 0;

	indices[12] = 3; indices[13] = 7; indices[14] = 6;
	indices[15] = 6; indices[16] = 2; indices[17] = 3;
	
	indices[18] = 2; indices[19] = 6; indices[20] = 5;
	indices[21] = 5; indices[22] = 1; indices[23] = 2;

	indices[24] = 1; indices[25] = 5; indices[26] = 4;
	indices[27] = 4; indices[28] = 0; indices[29] = 1;

	indices[30] = 4; indices[31] = 5; indices[32] = 6;
	indices[33] = 6; indices[34] = 7; indices[35] = 4;

	mainMesh->CreateMesh(vertices, indices, 24, 36);
}

void Cube::RenderCube()
{
	mainMesh->RenderMesh();
}

Cube::~Cube()
{
	delete(mainMesh);
}
