#include "TestCameraChange.h"
#include "camera.h"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include "../source/sdltiming.hpp"
#include "KeyInputs.hpp"
#include "SDL2/SDL.h"
#include <time.h>
#include <Windows.h>

void processMessages(double delta, TestEventHandler& eventHandler)
{
	SDL_Event e;
	(void)delta;

	while (SDL_PollEvent(&e)) {
		std::cout << "Type: " << e.type << std::endl;
		switch (e.type) {
		case SDL_KEYDOWN:
			eventHandler.onKeyDown(e.key.keysym.scancode, e.key.repeat != 0);
			std::cout << "KEYDOWN: " << e.type << std::endl;
			break;
		case SDL_KEYUP:
			eventHandler.onKeyUp(e.key.keysym.scancode, e.key.repeat != 0);
			std::cout << "KEYUP: " << e.type << std::endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			eventHandler.onMouseDown(e.button.button, 1);
			std::cout << "MOUSEDOWN: " << e.type << std::endl;
			break;
		case SDL_MOUSEBUTTONUP:
			eventHandler.onMouseUp(e.button.button, 1);
			std::cout << "MOUSEUP: " << e.type << std::endl;
			break;
			//case SDL_MOUSEMOTION:
				//eventHandler.onMouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
				//break;
		default:
			break;
		};
	}
}

test::TestCameraChange::TestCameraChange()
	//: m_Mesh("./res/TAL16OBJ.obj"), m_Shader("./res/basicShader"), m_Texture("./res/TALTS.jpg"),
	//m_Camera(glm::vec3(0.0f, 0.0f, -20.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), 70.0f, (float)960 / (float)540, 0.1f, 100.0f),
	//m_Display(960, 540, "OpenGL")
{
	buttonState = 0;
	prevButtonState = buttonState;
	posUpdate = false;
	//lastTime = SDLTiming::getTime();
	//
	//InputControl* horizontal = new InputControl();
	//InputControl* vertical = new InputControl();
	//InputControl* forward = new InputControl();

	//eventHandler.addKeyControl((KeyInputs::KEY_A), *horizontal, 1.f);
	//eventHandler.addKeyControl((KeyInputs::KEY_D), *horizontal, -1.f);
	//eventHandler.addKeyControl((KeyInputs::KEY_W), *vertical, 1.f);
	//eventHandler.addKeyControl((KeyInputs::KEY_S), *vertical, -1.f);
}

test::TestCameraChange::~TestCameraChange()
{

}

void test::TestCameraChange::OnRender(float updateTime)
{

	//if (m_ShouldRender)
	//{
		//m_Shader.Bind();
		//m_Texture.Bind();
		//m_Shader.Update(m_Transform, m_Camera);
		//m_Mesh.Draw();
		//m_Display.SwapBuffers();
	//}
	//else
	//{
	//	Sleep(1);
	//}
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//display.SwapBuffers();

}

void test::TestCameraChange::OnImGuiRender()
{
	ImGui::BeginGroup();
	ImGui::RadioButton("Camera Position Top", &buttonState, 0);
	ImGui::RadioButton("Camera Position Side", &buttonState, 1);
	ImGui::RadioButton("Camera Position Behind", &buttonState, 2);
	ImGui::EndGroup();
}

void test::TestCameraChange::OnUpdate()
{
	//double frameTime = 1.0 / 60.0;
	//double currentTime = SDLTiming::getTime();
	//double passedTime = currentTime - lastTime;
	//lastTime = currentTime;

	//frameCounter += passedTime;
	//m_UpdateTime += passedTime;

	//if (frameCounter >= 1.0)
	//{
	//	//double msPerFrame = 1000.0 / (double)fps;
	//	frameCounter = 0;
	//	//fps = 0;
	//}

	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplSDL2_NewFrame(m_Display.GetWindow());

	//ImGui::NewFrame();

	//m_ShouldRender = false;

	//while (m_UpdateTime >= frameTime)
	//{
	//	processMessages(frameTime, eventHandler);
	//	xPos += 10.f * frameTime * horizontal->getAmt();
	//	yPos += 10.f * frameTime * vertical->getAmt();
	//	m_Transform.GetPos()->x = xPos;
	//	m_Transform.GetPos()->y = yPos;
	//	m_Transform.GetPos()->z = zPos;


	//	m_UpdateTime -= frameTime;
	//	m_ShouldRender = true;
	//}

	//m_Display.Clear(0.1f, 0.1f, 0.8f, 1.0f);

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, -20.f);
	glm::vec3 forward = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

	if (prevButtonState != buttonState || posUpdate == true)
	{


		switch (buttonState)
		{
		case 0:
		{
			forward = glm::vec3(0.f, 0.f, 1.f);
			up = glm::vec3(0.f, 1.f, 0.f);
			pos = glm::vec3(0.f, 0.f, -20.f);
			prevButtonState = buttonState;
			posUpdate = false;
			break;
		}
		case 1:
		{
			forward = glm::vec3(1.f, 0.f, 0.f);
			up = glm::vec3(0.f, 0.f, -1.f);
			pos = glm::vec3(-10.f, 0.f, 0.f);
			prevButtonState = buttonState;
			posUpdate = false;
			break;
		}
		case 2:
		{
			forward = glm::vec3(0.f, 1.f, 0.f);
			up = glm::vec3(0.f, 0.f, -1.f);
			pos = glm::vec3(0.f, -10.f, 0.f);
			prevButtonState = buttonState;
			posUpdate = false;
			break;
		}
		default:
			std::cout << "Invalid Button State" << std::endl;
			break;
		}
		//m_Camera.SetCameraPosition(pos);
		//m_Camera.SetCameraForward(forward);
		//m_Camera.SetCameraUp(up);
	}
}
