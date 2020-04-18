#pragma once

#include "Tests.h"
#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "Texture.h"
#include "transform.h"
#include "TestEventHandler.hpp"
#include "InputControl.hpp"
#include "display.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace test {
	class TestCameraChange : public Tests
	{
	public:
		TestCameraChange();
		~TestCameraChange();
		void OnUpdate(double& updateTime, bool& isRunning);
		void OnRender(float updateTime);
		void OnImGuiRender();
		void OnEventUpdate();
		void UpdateTransform(Transform& t);

	private:
		//glm::mat4 projection;
		//glm::vec3 pos;
		//glm::vec3 forward;
		//glm::vec3 up;
		int buttonState, prevButtonState;
		bool posUpdate;

		//InputControl* horizontal;
		//InputControl* vertical;
		//TestEventHandler eventHandler;
		//Mesh m_Mesh;
		//Shader m_Shader;
		//Texture m_Texture;
		//Camera m_Camera;
		//Transform m_Transform;
		//Display m_Display;
	};
}
