#include <iostream>
#include "SimpleControl.h"
#include "source/KeyInputs.hpp"
#include "SDL2/SDL.h"

void SimpleControl::processMessages(double delta, TestEventHandler& eventHandler, bool& isRunning)
{
	//bool isRunning;
	SDL_Event e;
	(void)delta;

	while (SDL_PollEvent(&e)) {
		std::cout << "Type: " << e.type << std::endl;
		switch (e.type) {
		case SDL_KEYDOWN:
			//isRunning = true;
			eventHandler.onKeyDown(e.key.keysym.scancode, e.key.repeat != 0);
			std::cout << "KEYDOWN: " << e.type << std::endl;
			break;
		case SDL_KEYUP:
			//isRunning = true;
			eventHandler.onKeyUp(e.key.keysym.scancode, e.key.repeat != 0);
			std::cout << "KEYUP: " << e.type << std::endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//isRunning = true;
			eventHandler.onMouseDown(e.button.button, 1);
			std::cout << "MOUSEDOWN: " << e.type << std::endl;
			break;
		case SDL_MOUSEBUTTONUP:
			//isRunning = true;
			eventHandler.onMouseUp(e.button.button, 1);
			std::cout << "MOUSEUP: " << e.type << std::endl;
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
			//case SDL_MOUSEMOTION:
				//eventHandler.onMouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
				//break;
		default:
			//isRunning = true;
			break;
		};
	}
	//return isRunning;
}

SimpleControl::SimpleControl()
{
	horizontal = new InputControl();
	vertical = new InputControl();
	xPos = 0;
	yPos = 0;
	e.addKeyControl((KeyInputs::KEY_A), *horizontal, 1.f);
	e.addKeyControl((KeyInputs::KEY_D), *horizontal, -1.f);
	e.addKeyControl((KeyInputs::KEY_W), *vertical, 1.f);
	e.addKeyControl((KeyInputs::KEY_S), *vertical, -1.f);
}

void SimpleControl::UpdatePosition(Transform& t, bool& isRunning)
{
	float frameTime = 1.0 / 60.0;
	//bool isRunning;

	processMessages(frameTime, e, isRunning);

	xPos += 10.f * frameTime * horizontal->getAmt();
	yPos += 10.f * frameTime * vertical->getAmt();
	t.GetPos()->x = xPos;
	t.GetPos()->y = yPos;

	//return isRunning;
}