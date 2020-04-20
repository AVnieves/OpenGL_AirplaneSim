#include <iostream>
#include "source/Tests.h"
#include "source/sdltiming.hpp"
#include "TestTexture.h"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <math.h>
#include "terrain.h"

test::TestTexture::TestTexture()
	: m_Shader("./res/basicShader"), m_Texture("./res/bricks.jpg"),
	m_Camera(glm::vec3(0.0f, 0.0f, -20.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), 70.0f, (float)960 / (float)540, 0.1f, 100.0f)

{
	//std::vector <glm::vec3> points;
	//std::vector <glm::vec2> texCoords;
	//std::vector <glm::vec3> normals;
	glm::vec3 points;
	glm::vec2 texCoords;
	glm::vec3 normals;

	const static int numVertices = 128;
	float z;
	int vertexCount = 0;
	const static int size = numVertices* numVertices;

	Vertex vertices[size]; 
	unsigned int indices[6*(numVertices - 1)*(numVertices - 1)];
	int rem1, rem2;

	for (int y = -numVertices/2 ; y < numVertices/2; y++)
	{
		for (int x = -numVertices/2; x < numVertices/2; x++)
		{
			points = (glm::vec3((float)x, (float)y, -1));
			if (x % 2 == 0 && y % 2 == 0)
				texCoords = glm::vec2(0.f, 0.f);
			else if (x % 2 != 0 && y % 2 == 0)
				texCoords = glm::vec2(20.f, 0.f);
			else if (x % 2 == 0 && y % 2 != 0)
				texCoords = glm::vec2(0.f, 20.f);
			else
				texCoords = glm::vec2(20.f, 20.f);
			//texCoords = (glm::vec2((float)x, (float)y));
			normals = (glm::vec3(0, 0, -1));
			vertices[vertexCount].SetPos(points);
			vertices[vertexCount].SetTexCoord(texCoords);
			vertices[vertexCount].SetNormal(normals);
			vertexCount++;
		}
	}

	int indicesCount = 0;
	for (int y = 0; y < numVertices - 1; y++)
	{
		for (int x = 0; x < numVertices - 1; x++)
		{
			int bLeft = (y * numVertices) + x;
			int bRight = bLeft + 1;
			int tLeft = ((y + 1) * numVertices) + x;
			int tRight = tLeft + 1;
			indices[indicesCount++] = bLeft;
			indices[indicesCount++] = tLeft;
			indices[indicesCount++] = bRight;
			indices[indicesCount++] = tLeft;
			indices[indicesCount++] = tRight;
			indices[indicesCount++] = bRight;
		}
	}

	m_Mesh.GenerateMesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	//m_LastTime = SDLTiming::getTime();
	forward = glm::vec3(0.f, 0.f, 1.f);
	up = glm::vec3(0.f, 1.f, 0.f);
	pos = glm::vec3(0.f, 0.f, -10.f);	

	m_Camera.SetCameraPosition(pos);
	m_Camera.SetCameraForward(forward);
	m_Camera.SetCameraUp(up);

	m_ButtonState = 0;
	m_PrevButtonState = m_ButtonState;
	m_CameraPitch = 0;
}

test::TestTexture::~TestTexture()
{

}

void test::TestTexture::OnUpdate(double& updateTime, bool& isRunning)
{

	if (m_PrevButtonState != m_ButtonState)
	{
		switch (m_ButtonState)
		{
		case 0:
		{
			forward = glm::vec3(0.f, 0.f, 1.f);
			up = glm::vec3(0.f, 1.f, 0.f);
			pos = glm::vec3(0.f, 0.f, -20.f);
			m_PrevButtonState = m_ButtonState;
			break;
		}
		case 1:
		{
			forward = glm::vec3(1.f, 0.f, 0.f);
			up = glm::vec3(0.f, 0.f, -1.f);
			pos = glm::vec3(-10.f, 0.f, 0.f);
			m_PrevButtonState = m_ButtonState;
			break;
		}
		case 2:
		{
			forward = glm::vec3(0.f, 1.f, 0.f);
			up = glm::vec3(0.f, 0.f, -1.f);
			pos = glm::vec3(0.f, -10.f, 0.f);
			m_PrevButtonState = m_ButtonState;
			break;
		}
		default:
			std::cout << "Invalid Button State" << std::endl;
			break;
		}
		m_Camera.SetCameraPosition(pos);
		m_Camera.SetCameraForward(forward);
		m_Camera.SetCameraUp(up);
	}
	m_Camera.SetCameraPosition(pos);
	m_Camera.SetCameraForward(forward);
	m_Camera.SetCameraUp(up);
}

void test::TestTexture::OnImGuiRender()
{
	ImGui::BeginGroup();
	ImGui::RadioButton("Camera Position Top", &m_ButtonState, 0);
	ImGui::RadioButton("Camera Position Side", &m_ButtonState, 1);
	ImGui::RadioButton("Camera Position Behind", &m_ButtonState, 2);
	ImGui::SliderFloat2("Camera Position x, y", &pos.x, -20, 300);
	ImGui::SliderFloat("Camera Position z", &pos.z, -40, 0);
	ImGui::SliderFloat2("Camera Forward", &forward.x, -100, 100);
	ImGui::SliderFloat("Camera Forward z", &forward.z, -100, 100);
	//ImGui::SliderFloat2("Camera Up", &up.x, -10, 10);
	//ImGui::SliderFloat("Camera Up", &up.z, -10, 10);
	ImGui::EndGroup();
}

void test::TestTexture::OnRender(float updateTime)
{
	m_Shader.Bind();
	m_Texture.Bind();
	m_Shader.Update(m_Transform, m_Camera);
	m_Mesh.Draw();
}

void test::TestTexture::OnEventUpdate(TestEventHandler& eventHandler)
{
	// inputs:
	// INput events????
	//bool isRunning;
	//simpleControl.processMessages(0.0, eventHandler, isRunning);
	
	// 1. Process events;
	// 2. 
}

void test::TestTexture::UpdateTransform(Transform& t)
{
	//m_Transform = t;
}

