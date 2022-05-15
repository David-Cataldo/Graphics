// PRECOMPILED HEADER
#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION

// ALL INCLUDED IN PRECOMPILED HEADER
//#include <stdio.h>
//#include <string.h>
//#include <cmath>
//#include <vector>

//#include <GL\glew.h>
//#include <GLFW\glfw3.h>

//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>



#include <chrono>
#include <sys/timeb.h>
#include <ctime>
#include <memory>
#include "wtypes.h"

#include "MyWindow.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"	
#include "Material.h"
#include "CommonValues.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Model.h"
#include "Skybox.h"

RECT rcScreen;

const float toRadians = 3.14159265f / 180.0f;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePos = 0,
uniformSpecularIntensity = 0, uniformShine = 0, 
uniformOmniLightPos = 0, uniformFarPlane = 0;


MyWindow mainWindow;
std::vector<Shader> shaderList;
Shader directionalShadowShader;
Shader omniShadowShader;

Skybox skybox;

Camera camera;
long frames = 0;
double mtime;


Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMat;
Material dullMat;

bool isActive = true;

std::unique_ptr<Model> car (new Model);
Model tank;

GLfloat pos = 0.0f;
GLfloat mult = 0.01f;
GLfloat rot = 0.0f;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

GLfloat IMrot = 0;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert.txt";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag.txt";

std::unique_ptr<Model> RayCast(glm::vec3 pos, glm::vec3 dir, GLfloat dist)
{

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert.txt", "Shaders/directional_shadow_map.frag.txt");
	omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert.txt", "Shaders/omni_shadow_map.geom.txt", "Shaders/omni_shadow_map.frag.txt");

}

void RenderScene()
{

	glm::mat4 model(1.0f);

	IMrot += 0.6;
	if (IMrot > 360.0)
	{
		IMrot = 0.1;
	}


	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, -1.5f, 0.0f));
	model = glm::rotate(model, IMrot * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 35.0f * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
	//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	shinyMat.UseMaterial(uniformSpecularIntensity, uniformShine);
	car->RenderModel();
	if (!isActive)
	{
		car.reset();
	}
}

void DirectionalShadowMapPass(DirectionalLight* light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLighttransform(&light->CalculateLightTransform());

	directionalShadowShader.Validate("Directional");

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight* light)
{
	omniShadowShader.UseShader();

	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = omniShadowShader.GetModelLocation();
	uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
	uniformFarPlane = omniShadowShader.GetFarPlaneLocation();

	glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
	glUniform1f(uniformFarPlane, light->GetFarPlane());
	omniShadowShader.SetLightMatrices(light->CalculateLightTransform());

	omniShadowShader.Validate("omni");

	RenderScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	mainWindow.UpdateSize();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[0].UseShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformEyePos = shaderList[0].GetEyePosLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShine = shaderList[0].GetShineLocation();

	//glViewport(0, 0, 1600, 1400);

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePos, camera.getCameraPos().x, camera.getCameraPos().y, camera.getCameraPos().z);

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount, 3, 0);
	shaderList[0].SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
	shaderList[0].SetDirectionalLighttransform(&mainLight.CalculateLightTransform());

	mainLight.GetShadowMap()->Read(GL_TEXTURE2);

	shaderList[0].SetTexture(1);
	shaderList[0].SetDirectionalShadowMap(2);
	

	glm::vec3 flashLight = camera.getCameraPos();
	flashLight.y -= 0.3f;
	flashLight.x -= 0.3f;
	//spotLights[0].SetFlash(flashLight, camera.GetCameraDirection());

	shaderList[0].Validate("norm");

	RenderScene();
}

int main()
{
	mtime = time(nullptr);
	GetWindowRect(GetDesktopWindow(), &rcScreen);

	mainWindow = MyWindow(rcScreen.right*1.5, rcScreen.bottom*1.5);
	mainWindow.Initialise();

	CreateShaders();

	Assimp::Importer im;

	camera = Camera(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.15f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();

	shinyMat = Material(4.0f, 256);
	dullMat = Material(0.3f, 4);

	
	car->LoadModel("Models/Ironman.obj");

	tank.LoadModel("Models/old_tank.obj");

	mainLight = DirectionalLight(4096, 4096,
								glm::vec3(9.0f, 0.45f, 0.17f), 0.1f,
								glm::vec3(-10.0f, -12.0f, 18.5f), 0.5f);


	pointLights[0] = PointLight(1024, 1024, 0.01f, 100.0f,
								glm::vec3(1.0f, 1.0f, 0.0f),
								0.0f, 1.0f,
								glm::vec3(-4.0f, 0.0f, 0.0f),
								0.3f, 0.2f, 0.1f);

	pointLightCount++;

	pointLights[1] = PointLight(1024, 1024, 0.01f, 100.0f, glm::vec3(0.0f, 0.0f, 1.0f),
								0.0f, 1.0f,
								glm::vec3(1.0f, 0.0f, -2.0f),
								0.3f, 0.2f, 0.1f);
	pointLightCount++;


	spotLights[0] = SpotLight(1024, 1024, 0.01f, 100.0f, 
								glm::vec3(1.0f, 1.0f, 1.0f),
								0.0f, 2.0f,
								glm::vec3(0.0f, 10.0f, 0.0f),
								glm::vec3(0.0f, -1.0f, 0.0f),
								1.0f, 0.0f, 0.0f,
								10.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(1024, 1024, 0.01f, 100.0f, 
								glm::vec3(1.0f, 1.0f, 1.0f),
								0.0f, 1.0f,
								glm::vec3(3.5f, 0.01f, 0.0f),
								glm::vec3(0.9f, -1.0f, 0.0f),
								1.0f, 0.0f, 0.0f,
								20.0f);
	spotLightCount++;

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);


	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");


	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		frames++;
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		if (!io.WantCaptureMouse)
		{
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(), mainWindow.getMouseLeftClicking());
		}
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		if (mainWindow.getMouseLeftClicking())
		{
			//std::cout << "X: " << mainWindow.getMouseX() << "  Y: " << mainWindow.getMouseY() << std::endl;
		}

		if (mainWindow.getsKeys()[GLFW_KEY_L])
		{
			spotLights[0].Toggle();
			mainWindow.getsKeys()[GLFW_KEY_L] = false;
			std::cout << spotLights[0].IsOn() << std::endl;
		}

		if (frames % 10 == 0)
		{
			DirectionalShadowMapPass(&mainLight);
		}
		else if (frames % 6 == 2)
		{
			for (size_t i = 0; i < pointLightCount; i++)
			{
				OmniShadowMapPass(&pointLights[i]);
			}
		}
		else if (frames % 6 == 4)
		{
			for (size_t i = 0; i < spotLightCount; i++)
			{
				OmniShadowMapPass(&spotLights[i]);
			}
		}
		RenderPass(projection, camera.calculateViewMatrix());
		
		
		ImGui::SetNextWindowPos(ImVec2(3 * mainWindow.getWidth() / 4, 0));
		ImGui::SetNextWindowSize(ImVec2(mainWindow.getWidth() / 4, mainWindow.getHeight()/2));
		ImGui::Begin("Scene Objects");
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(3 * mainWindow.getWidth() / 4, mainWindow.getHeight()/2));
		ImGui::SetNextWindowSize(ImVec2(mainWindow.getWidth() / 4, mainWindow.getHeight() / 2));
		ImGui::Begin("Object Info");
		ImGui::Text("X: "); ImGui::SameLine();
		ImGui::InputFloat("", &pos);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//glUseProgram(0);

		mainWindow.swapBuffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	std::cout << frames / (time(nullptr) - mtime) << std::endl;
	std::cout << (time(nullptr) - mtime);

	return 0;
}