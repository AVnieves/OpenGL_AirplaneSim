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
	m_Camera(glm::vec3(0.0f, 0.0f, -20.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), 70.0f, (float)960 / (float)540, 0.1f, 100.0f)

{
	forward = glm::vec3(1.f, 0.f, 0.f);
	up = glm::vec3(0.f, 0.f, -1.f);
	//pos = glm::vec3(0.f, 0.f, -20.f);	
	pos = glm::vec3(0.f, 0.f, -1.75f);

	m_Camera.SetCameraPosition(pos);
	m_Camera.SetCameraForward(forward);
	m_Camera.SetCameraUp(up);

	m_ButtonState = 0;
	m_PrevButtonState = m_ButtonState;
	//m_Transform.GetRot()->y = 3.14;
	m_CameraPitch = 0;
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

void test::TestTextureObject::OnImGuiRender()
{
	ImGui::BeginGroup();
	ImGui::RadioButton("Camera Position Top", &m_ButtonState, 0);
	ImGui::RadioButton("Camera Position Side", &m_ButtonState, 1);
	ImGui::RadioButton("Camera Position Behind", &m_ButtonState, 2);
	ImGui::SliderFloat2("Camera Position x, y", &pos.x, -10, 10);
	ImGui::SliderFloat("Camera Position z", &pos.z, -40, 0);
	ImGui::SliderFloat2("Camera Forward", &forward.x, -10, 10);
	ImGui::SliderFloat("Camera Forward z", &forward.z, -10, 10);
	//ImGui::SliderFloat2("Camera Up", &up.x, -10, 10);
	//ImGui::SliderFloat("Camera Up", &up.z, -10, 10);
	ImGui::EndGroup();
}

void test::TestTextureObject::OnRender(float updateTime)
{
	Transform t;
	
	//m_Terrain.Draw(m_Camera,t);
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
	//m_Camera = c;
	pos = *c.GetPos();

}

