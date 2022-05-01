#pragma once

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocatiom, const char* fragmentLocation);
	
	std::string ReadFile(const char* fileLocation);

	void UseShader();
	void ClearShader();

	GLuint GetProjectionLocation() { return uniformProjection; }
	GLuint GetModelLocation() { return uniformModel; }
	GLuint GetViewLocation() { return uniformView; }
	GLuint GetAmbientIntensityLocation() { return uniformDirectionalLight.uniformAmbientIntensity; }
	GLuint GetAmbientColorLocation() { return uniformDirectionalLight.uniformColor; }
	GLuint GetDiffuseIntensityLocation() { return uniformDirectionalLight.uniformDiffuseIntensity; }
	GLuint GetDirectionLocation() { return uniformDirectionalLight.uniformDirection; }
	GLuint GetSpecularIntensityLocation() { return uniformSpecularIntensity; }
	GLuint GetShineLocation() { return uniformShine; }
	GLuint GetEyePosLocation() { return uniformEyePos; }

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLighttransform(glm::mat4* lTransform);


	void UsePhongLighting(bool b);

	~Shader();

private:
	int pointLightCount;
	int spotLightCount;

	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePos,
		uniformSpecularIntensity, uniformShine,
		uniformTexture,
		uniformDirectionalLightTransform, uniformDirectionalShadowMap;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		
		GLuint uniformDirection;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	GLuint uniformSpotLightCount;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

