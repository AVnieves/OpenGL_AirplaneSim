#include <iostream>
#include "source/Tests.h"
#include "source/sdltiming.hpp"
#include "TestTextureGrid.h"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include "CameraControl.h"

test::TestTextureGrid::TestTextureGrid()
	: m_Camera(glm::vec3(0.0f, -9.5f, -1.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 70.0f, (float)960 / (float)540, 0.1f, 100.0f),
	m_Terrain(30, 2), m_T38Mesh("./res/TAL16OBJ.obj"), m_T38Texture("./res/TALTS.jpg"), m_Shader("./res/basicShader")
{
	forward = glm::vec3(0.f, 1.f, 0.f);
	up = glm::vec3(0.f, 0.f, -1.f);
	pos = glm::vec3(m_T38Transform.GetPos()->x, m_T38Transform.GetPos()->y - 9.5f, m_T38Transform.GetPos()->z - 1.75f);
	
	m_Camera.SetCameraPosition(pos);
	m_Camera.SetCameraForward(forward);
	m_Camera.SetCameraUp(up);

	m_ButtonState = 0;
	m_PrevButtonState = m_ButtonState;
	m_CameraPitch = 0;
	glm::vec3 temp = glm::vec3(pos.x,pos.y,0);

	m_TransformTerrain.SetPos(temp);
}

test::TestTextureGrid::~TestTextureGrid()
{

}

void test::TestTextureGrid::OnUpdate(double& updateTime, bool& isRunning)
{
	
	if (m_PrevButtonState != m_ButtonState)
	{
		switch (m_ButtonState)
		{
			case 1:
			{
				forward = glm::vec3(1.f, 0.f, 0.f);
				up = glm::vec3(0.f, 0.f, -1.f);
				//pos = glm::vec3(-10.f, 0.f, 0.f);
				pos = glm::vec3(m_T38Transform.GetPos()->x - 10.f, m_T38Transform.GetPos()->y, m_T38Transform.GetPos()->z);
				m_PrevButtonState = m_ButtonState;
				m_Camera.GetPos()->x = pos.x;
				m_Camera.GetPos()->y = pos.y;
				m_Camera.GetPos()->z = pos.z;
				m_Camera.GetForward()->x = forward.x;
				m_Camera.GetForward()->y = forward.y;
				m_Camera.GetForward()->z = forward.z;
				m_Camera.GetUp()->x = up.x;
				m_Camera.GetUp()->y = up.y;
				m_Camera.GetUp()->z = up.z;
				break;
			}
			case 2:
			{
				forward = glm::vec3(0.f, 1.f, 0.f);
				up = glm::vec3(0.f, 0.f, -1.f);
				//pos = glm::vec3(0.f, -9.5f, -1.5f);
				pos = glm::vec3(m_T38Transform.GetPos()->x, m_T38Transform.GetPos()->y - 9.5f, m_T38Transform.GetPos()->z - 1.5f);
				m_PrevButtonState = m_ButtonState;
				m_Camera.GetPos()->x = pos.x;
				m_Camera.GetPos()->y = pos.y;
				m_Camera.GetPos()->z = pos.z;
				m_Camera.GetForward()->x = forward.x;
				m_Camera.GetForward()->y = forward.y;
				m_Camera.GetForward()->z = forward.z;
				m_Camera.GetUp()->x = up.x;
				m_Camera.GetUp()->y = up.y;
				m_Camera.GetUp()->z = up.z;
				break;
			}
			default:
			{
				std::cout << "Invalid Button State" << std::endl;
				break;
			}
		}
	}
	else
	{
		pos = glm::vec3(m_T38Transform.GetPos()->x, m_T38Transform.GetPos()->y - 9.5f, m_T38Transform.GetPos()->z - 1.5f);

		m_Camera.GetPos()->x = pos.x;
		m_Camera.GetPos()->y = pos.y;
		m_Camera.GetPos()->z = pos.z;
		m_Camera.GetForward()->x = forward.x;
		m_Camera.GetForward()->y = forward.y;
		m_Camera.GetForward()->z = forward.z;
		m_Camera.GetUp()->x = up.x;
		m_Camera.GetUp()->y = up.y;
		m_Camera.GetUp()->z = up.z;
	}
}

void test::TestTextureGrid::OnImGuiRender()
{
	
	ImGui::BeginGroup();
	ImGui::RadioButton("Camera Position Side", &m_ButtonState, 1);
	ImGui::RadioButton("Camera Position Behind", &m_ButtonState, 2);
	ImGui::SliderFloat2("Camera Forward", &forward.x, -10, 10);
	ImGui::SliderFloat("Camera Forward z", &forward.z, -10, 10);
	ImGui::EndGroup();
	
	//m_Camera.SetCameraPosition(pos);
	//m_Camera.SetCameraForward(forward);
}

void test::TestTextureGrid::OnRender(float updateTime)
{
	//Transform t;
	int temp = (int)m_Camera.GetPos()->y % 64;
	int temp2 = (int)m_Camera.GetPos()-> x % 64;
	bool UpdateTerrain = false;

	if (temp == 50)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(0.f, 78.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}

	if (temp == -50)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(0.f, -78.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}

	if (temp2 == 50)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(-78.f, 0.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}
	if (temp2 == -50)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(78.f, 0.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}

	m_Terrain.Draw(m_Camera, m_TransformTerrain);
	m_Shader.Bind();
	m_T38Texture.Bind();
	m_Shader.Update(m_T38Transform, m_Camera);
	m_T38Mesh.Draw();
}

void test::TestTextureGrid::OnEventUpdate(TestEventHandler& eventHandler)
{
	// Events to update 
}

void test::TestTextureGrid::UpdateTransform(Transform& t)
{
	m_T38Transform = t;
}

void test::TestTextureGrid::UpdateCamera(Camera& c)
{
	pos = *c.GetPos();
}