#pragma once

#include "stb_image.h"

class Texture
{
public:
	Texture(const char* fileLoc = "");

	bool LoadTexture();
	bool LoadTextureA();

	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};

