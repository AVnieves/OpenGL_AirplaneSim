#pragma once
#include "source/InputControl.hpp"
#include "source/TestEventHandler.hpp"
#include "source/transform.h"

class SimpleControl
{

public:
	SimpleControl();
	//~SimpleControl();
	void UpdatePosition(Transform& t, bool& isRunning);

private:
	InputControl* horizontal;
	InputControl* vertical;
	TestEventHandler e;
	float xPos, yPos;
	void processMessages(double, TestEventHandler&, bool&);
};