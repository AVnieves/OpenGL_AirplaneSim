#include "TestEventHandler.hpp"
#include <iostream>
#include "IApplicationEventHandler.h"
#include "InputControl.hpp"
#include "KeyInputs.hpp"

#define MOUSE_OFFSET KeyInputs::NUM_KEYS


void TestEventHandler::onKeyDown(int keyCode, bool isRepeat)
{

	updateInput(keyCode, 1.f, isRepeat);
}

void TestEventHandler::onKeyUp(int keyCode, bool isRepeat)
{
	updateInput(keyCode, -1.f, isRepeat);
}

void TestEventHandler::onMouseDown(int mouseButton, unsigned int numClicks)
{
	updateInput(mouseButton + MOUSE_OFFSET, 1.f, false);
}

void TestEventHandler::onMouseUp(int mouseButton, unsigned int numClicks)
{
	updateInput(mouseButton + MOUSE_OFFSET, -1.f, false);
}

void TestEventHandler::addKeyControl(int keyCode, InputControl& i, float weight)
{
	inputEvents[keyCode].push_back(std::pair< float, InputControl& >(weight, i));

}
void TestEventHandler::addMouseControl(int keyCode, InputControl& i, float weight)
{
	inputEvents[keyCode+MOUSE_OFFSET].push_back(std::pair< float, InputControl& >(weight, i));
}

void TestEventHandler::updateInput(int inputCode, float dir, bool isRepeat)
{
	if (isRepeat)
	{
		return;
	}

	
	for (unsigned int j = 0; j < inputEvents[inputCode].size(); j++)
	{
		std::cout << "Amount to add " << inputEvents[inputCode][j].first << std::endl;
		inputEvents[inputCode][j].second.addAmt(inputEvents[inputCode][j].first * dir);
	}
	
}
