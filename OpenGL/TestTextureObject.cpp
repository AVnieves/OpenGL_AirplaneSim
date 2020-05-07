#include <iostream>
#include "source/Tests.h"
#include "source/sdltiming.hpp"
#include "TestTextureObject.h"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include "CameraControl.h"

test::TestTextureObject::TestTextureObject()
	: m_Mesh("./res/TAL16OBJ.obj"), m_Shader("./res/basicShader"), m_Texture("./res/TALTS.jpg"),
	m_Camera(glm::vec3(0.0f, -9.5f, -1.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 70.0f, (float)960 / (float)540, 0.1f, 100.0f)
	
{
	forward = glm::vec3(0.f, 1.f, 0.f);
	up = glm::vec3(0.f, 0.f, -1.f);
	pos = glm::vec3(0.f, -9.5f, -1.75f);

	//m_Camera.SetCameraPosition(pos);
	//m_Camera.SetCameraForward(forward);
	//m_Camera.SetCameraUp(up);

	m_ButtonState = 0;
	m_PrevButtonState = m_ButtonState;
	m_CameraPitch = 0;
	glm::vec3 temp = glm::vec3(pos.x,pos.y,0);

	m_TransformTerrain.SetPos(temp);
}

test::TestTextureObject::~TestTextureObject()
{

}

void test::TestTextureObject::OnUpdate(double& updateTime, bool& isRunning)
{

	if (m_PrevButtonState != m_ButtonState)
	{
		switch (m_ButtonState)
		{
			case 0:
			{
				forward = glm::vec3(0.f, 0.f, 1.f);
				up = glm::vec3(0.f, 1.f, 0.f);
				pos = glm::vec3(-10.f, 0.f, 0.f);
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

				//m_Camera.SetCameraPosition(pos);
				//m_Camera.SetCameraForward(forward);
				//m_Camera.SetCameraUp(up);

				break;
			}
			case 1:
			{
				forward = glm::vec3(1.f, 0.f, 0.f);
				up = glm::vec3(0.f, 0.f, -1.f);
				pos = glm::vec3(-10.f, 0.f, 0.f);
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
				pos = glm::vec3(0.f, -9.5f, -1.5f);
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

void test::TestTextureObject::OnImGuiRender()
{
	ImGui::BeginGroup();
	ImGui::Text("Controls:");
	ImGui::Text("ASDW for airplane controls");
	ImGui::Text("Arrow keys for x, y camera controls");
	ImGui::Text("Z and space bar for z camera controls");
	ImGui::RadioButton("Camera Position Top", &m_ButtonState, 0);
	ImGui::RadioButton("Camera Position Side", &m_ButtonState, 1);
	ImGui::RadioButton("Camera Position Behind", &m_ButtonState, 2);
	ImGui::SliderFloat2("Camera Position x, y", &pos.x, -10, 10);
	ImGui::SliderFloat("Camera Position z", &pos.z, -40, 0);
	ImGui::SliderFloat2("Camera Forward", &forward.x, -10, 10);
	ImGui::SliderFloat("Camera Forward z", &forward.z, -10, 10);
	ImGui::EndGroup();
}

void test::TestTextureObject::OnRender(float updateTime)
{
	//Transform t;
	int temp = (int)m_Camera.GetPos()->y % 64;
	int temp2 = (int)m_Camera.GetPos()-> x % 64;
	bool UpdateTerrain = false;

	if (temp == 20)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(0.f, 78.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}

	if (temp == -20)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(0.f, -78.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}

	if (temp2 == 20)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(-78.f, 0.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}
	if (temp2 == -20)
	{
		glm::vec3 newPos = *m_Camera.GetPos() + glm::vec3(78.f, 0.f, 0.f);
		UpdateTerrain = true;
		m_TransformTerrain.SetPos(newPos);
	}

	//if (UpdateTerrain)
	//{
	//	m_TransformTerrain.SetPos()
	//}

	m_Terrain.Draw(m_Camera,m_TransformTerrain);
	m_Shader.Bind();
	m_Texture.Bind();
	m_Shader.Update(m_Transform, m_Camera);
	m_Mesh.Draw();
}

void test::TestTextureObject::OnEventUpdate(TestEventHandler& eventHandler)
{
	// inputs:
	// INput events????
	//bool isRunning;
	//simpleControl.processMessages(0.0, eventHandler, isRunning);
	
	// 1. Process events;
	// 2. 
}

void test::TestTextureObject::UpdateTransform(Transform& t)
{
	m_Transform = t;
}

void test::TestTextureObject::UpdateCamera(Camera& c)
{
	pos = *c.GetPos();
	//*m_Camera.GetPos() = *c.GetPos();
}

//void test::TestTextureObject::UpdateCamera2(Camera& c, glm::vec3 pos, glm::vec3 forward, glm::vec3 up)
//{
//
//}

