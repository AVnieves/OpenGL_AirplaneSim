#pragma once

#include "source/Tests.h"
#include "source/shader.h"
#include "SimpleControl.h"
#include "source/transform.h"
#include "source/texture.h"
#include "source/mesh.h"
#include "source/camera.h"

namespace test
{
	class TestTexture : public Tests
	{
	public:
		TestTexture();
		~TestTexture();
		void OnUpdate(double& updateTime, bool& isRunning);
		void OnImGuiRender();
		void OnRender(float updateTime);
		void OnEventUpdate(TestEventHandler& eventHandler);
		void UpdateTransform(Transform& t);
		//void UpdateCamera(Camera& c);
	private:
		int m_ButtonState;
		int m_PrevButtonState;
		float m_CameraPitch;
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;

		Shader m_Shader;
		//SimpleControl m_SimpleControl;
		Transform m_Transform;
		Texture m_Texture;
		Mesh m_Mesh;
		Camera m_Camera;
		//Vertex vertices[4];
	};

}
