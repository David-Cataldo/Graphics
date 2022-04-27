#pragma once

class Material
{
public:
	Material(GLfloat sIntensity = 0.0f, GLfloat sShine = 0.0f);

	void UseMaterial(GLuint specularIntensityLocation, GLuint shineLocation);

	~Material();

private:
	GLfloat specularIntensity;
	GLfloat shine;
};

