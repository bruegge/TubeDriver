#pragma once
#include <iostream>
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_glfw.h"
#include "../ImGUI/imgui_impl_opengl3.h"

#include "WindowGLFW.h"
#include "Camera.h"
#include "ModelObject.h"
#include "Shader.h"

CWindowGLFW* pWindow = nullptr;
CCamera* pCamera = nullptr;
CModel* pModel = nullptr;
CShader* pShader = nullptr;

void LoadContent()
{
	pWindow = new CWindowGLFW(800, 600);
	pCamera = new CCamera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 136, static_cast<float>(pWindow->GetWindowSize().x) / static_cast<float>(pWindow->GetWindowSize().y), 0.1f, 100.0f);
	pModel = new CModel("../AdditionalMaterial/Models/rohr.x");
	pShader = new CShader();
	pShader->CreateShaderProgram("../AdditionalMaterial/Shaders/VS_ShowTube.glsl", nullptr, nullptr, nullptr, "../AdditionalMaterial/Shaders/FS_ShowTube.glsl");
	
	
	{ //GUI
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(pWindow->GetWindowID(), true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}
}

void GameLoop()
{
	glClearColor(0.1f, 0.1f, 0.02f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool bExitGame = false;
	while (!bExitGame)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and the depth buffer

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bExitGame = pWindow->ManageInputs();

		pShader->Bind();
		GLint nUniformLocationViewProjectionMatrix = glGetUniformLocation(pShader->GetID(), "viewProjectionMatrix");
		glm::mat4 mViewProjectionMatrix = pCamera->GetViewProjectionMatrix();
		glUniformMatrix4fv(nUniformLocationViewProjectionMatrix, 1, GL_FALSE, &(mViewProjectionMatrix[0][0]));

		pModel->Draw(pShader);
		pShader->UnBind();

		{
			ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("%d / %d Cakes", pPlayer->GetCountCake(), pCakes->GetCountCakes());
			//ImGui::Text("%d Stones", pPlayer->GetCountStones());
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		pWindow->SwapBuffers();
	}

}

void DeleteContent()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete pWindow;
	delete pCamera;
}

void main()
{
	LoadContent();
	GameLoop();
	DeleteContent();
}
