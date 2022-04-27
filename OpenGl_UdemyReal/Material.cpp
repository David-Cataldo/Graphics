#include "pch.h"
#include "Material.h"

Material::Material(GLfloat sIntensity, GLfloat sShine)
{
	specularIntensity = sIntensity;
	shine = sShine;
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shineLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shineLocation, shine);
}

Material::~Material()
{

}
