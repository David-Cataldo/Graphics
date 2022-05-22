#pragma once


// in PCH
// #include <vector>
// #include <string>
// #include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void ClearModel();
	void Translate(GLfloat dist, PhySimsDirection dir);
	void Rotate(GLfloat angle, PhySimsAxis axis, PhySimsAngleMode AM);
	void Scale(GLfloat dist, PhySimsAxis axis);

	std::vector<Mesh*> GetMeshes() { return meshList; }
	glm::mat4 GetModel() { return model; }

	~Model();

private:

	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTex;

	glm::mat4 model;
};
