#pragma once

#include "source/Tests.h"
#include "source/shader.h"
#include "SimpleControl.h"
#include "source/transform.h"
#include "source/texture.h"
#include "source/mesh.h"
#include "source/camera.h"
#include "terrain2.h"

namespace test
{
	class TestTextureGrid : public Tests
	{
	public:
		TestTextureGrid();
		~TestTextureGrid();
		void OnUpdate(double& updateTime, bool& isRunning);
		void OnImGuiRender();
		void OnRender(float updateTime);
		void OnEventUpdate(TestEventHandler& eventHandler);
		void UpdateTransform(Transform& t);
		void UpdateCamera(Camera& c);
	private:
		int m_ButtonState;
		int m_PrevButtonState;
		float m_CameraPitch;
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;

		Mesh m_T38Mesh;
		Texture m_T38Texture;
		Transform m_T38Transform;
		Shader m_Shader;
		Camera m_Camera;
		Terrain2 m_Terrain;
		Transform m_TransformTerrain;
	};

}
