#pragma once
#include "source/InputControl.hpp"
#include "source/TestEventHandler.hpp"
#include "source/transform.h"

class AirplaneControl
{
public:
	inline AirplaneControl()
	{

	}

	inline ~AirplaneControl()
	{

	}

	inline void AddMovementControl(glm::vec3 pos, InputControl* ic)
	{
		movement.push_back(std::make_pair(pos, ic));
	}

	inline void UpdateTransform(Transform& t)
	{
		double frameTime = 1.0 / 60.0;
		double xPos, yPos, zPos;

		for (int i = 0; i < movement.size(); i++)
		{

		}
	}

private:
	std::vector<std::pair<glm::vec3, InputControl*>> movement;
	float velocity;

};
