#pragma once

#include <vector>
#include <map>
#include "IApplicationEventHandler.h"
#include "InputControl.hpp"

typedef std::map <int, std::vector<std::pair< float, InputControl& >>> Events;

class TestEventHandler : public IApplicationEventHandler
{

public:
	TestEventHandler();
	//~Test();

	void onKeyDown(int keyCode, bool isRepeat);
	void onKeyUp(int mouseButton, bool isRepeat);
	void onMouseDown(int mouseButton, unsigned int numClicks);
	void onMouseUp(int mouseButton, unsigned int numClicks);
	//virtual void onMouseMove(int32 mousePosX, int32 mousePosY,
	//int32 deltaX, int32 deltaY, InputControl& inputControl);
	//void addKeyControl(int keyCode, std::pair<InputControl, float> i);
	//void addMouseControl(int keyCode, std::pair<InputControl, float> i);
	void addKeyControl(int keyCode, InputControl& i, float weight = 1.f);
	void addMouseControl(int keyCode, InputControl& i, float weight = 1.f);
	void updateInput(int inputCode, float dir, bool isRepeat);
	//Events getInputEvents();



private:
	std::vector <std::pair<int, int>> testVector;
	std::vector <std::pair<InputControl, float>> testVector2;
	//std::map <int, std::vector<std::pair< float, InputControl& >>> inputEvents;
	Events inputEvents;
};

inline TestEventHandler::TestEventHandler()
{
	//testVector.push_back({ 0,0 });
	//InputControl input1;
	//testVector2.push_back({ input1,0 });
}
