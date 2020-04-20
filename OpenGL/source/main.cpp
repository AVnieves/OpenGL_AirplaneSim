// Entity component system
// system of entities and components
// component: raw data ( c struct)
// entity: list of components
// System: takes components and uses that for specific purpose
// logic is in system, data is in components and the connection is entity

// Start code based on the Bennybox youtube videos. 

#include <iostream>
#include <SDL2/SDL.h>
#include <time.h>
#include <Windows.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "IApplicationEventHandler.h"
#include "TestEventHandler.hpp"
#include "KeyInputs.hpp"
#include "sdltiming.hpp"
#include "Tests.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include "../TestFrameWork.h"
#include "../TestTexture.h"
#include "../TestTextureObject.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;


void processMessages(double delta, TestEventHandler& eventHandler, bool& isAppRunning)
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
		case SDL_QUIT:
			isAppRunning = false;
			break;
		default:
			break;
		};
	}
}

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh T38("./res/TAL16OBJ.obj");

	//Shader shader("./res/basicShader");
	//Texture texture("./res/TALTS.jpg");
	Transform transform;
	//Camera camera(glm::vec3(0.0f, 0.0f, -20.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	//SDL_Event e;
	bool isRunning = true;
	float xcounter = 0.0f;
	float ycounter = 0.0f;
	float zcounter = 0.0f;

	// control
	//float amt = 0.f;
	TestEventHandler eventHandler;
	InputControl* horizontal = new InputControl();
	InputControl* vertical = new InputControl();
	InputControl* lift = new InputControl();

	eventHandler.addKeyControl((KeyInputs::KEY_A), *horizontal, 1.f);
	eventHandler.addKeyControl((KeyInputs::KEY_D), *horizontal, -1.f);
	eventHandler.addKeyControl((KeyInputs::KEY_W), *vertical, 1.f);
	eventHandler.addKeyControl((KeyInputs::KEY_S), *vertical, -1.f);
	eventHandler.addMouseControl((KeyInputs::MOUSE_LEFT_BUTTON), *lift, -1.f);
	eventHandler.addMouseControl((KeyInputs::MOUSE_RIGHT_BUTTON), *lift, 1.f);

	SimpleControl movementControl;
	movementControl.AddMovementControls(glm::vec3(1.f, 0.f, 0.f), horizontal);
	movementControl.AddMovementControls(glm::vec3(0.f, 1.f, 0.f), vertical);
	movementControl.AddMovementControls(glm::vec3(0.f, 0.f, 1.f), lift);

	// Setup ImGui Context
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(display.GetWindow(), display.GetContext());
	ImGui_ImplOpenGL3_Init("#version 130");

	test::Tests* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	// add tests here:
	testMenu->AddTest<test::TestFrameWork>("Test Camera Postion");
	testMenu->AddTest<test::TestTexture>("Test Texture Plane");
	testMenu->AddTest<test::TestTextureObject>("Test Texture and Object");
	// frame updates
	unsigned int fps = 0;
	double lastTime = SDLTiming::getTime();
	double frameCounter = 0.0;
	double updateTime = 1.0;
	double* updateTimePtr = &updateTime;
	bool* isRunningPtr = &isRunning;
	float frameTime = 1.0 / 60.0;
	float xPos = 0.f;
	float yPos = 0.f;
	float zPos = 0.f;
	//transform.GetRot()->y = 3.14;
	transform.GetRot()->x = 3.14;

	while (isRunning)
	{
		display.Clear(0.1f, 0.1f, 0.8f, 1.0f);

		double currentTime = SDLTiming::getTime();
		double passedTime = currentTime - lastTime;
		lastTime = currentTime;

		frameCounter += passedTime;
		updateTime += passedTime;

		if (frameCounter >= 1.0)
		{
			double msPerFrame = 1000.0 / (double)fps;
			frameCounter = 0;
			fps = 0;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(display.GetWindow());
		ImGui::NewFrame();

		if (currentTest)
		{
			bool shouldRender = false;

			while (updateTime >= frameTime)
			{
				processMessages(updateTime, eventHandler, isRunning);
				movementControl.UpdateTransform(transform);
				currentTest->UpdateTransform(transform);
				currentTest->OnUpdate(updateTime, isRunning);
				updateTime -= frameTime;
				shouldRender = true;
			}

			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (shouldRender)
			{
				currentTest->OnRender(updateTime);
				display.SwapBuffers();
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}
			else
			{
				Sleep(1);
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}
		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return 0;
}