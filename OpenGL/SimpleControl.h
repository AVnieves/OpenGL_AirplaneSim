#pragma once
#include "source/InputControl.hpp"
#include "source/TestEventHandler.hpp"
#include "source/transform.h"

class SimpleControl
{
public:
	inline SimpleControl()
	{

	}

	inline ~SimpleControl()
	{

	}

	inline void AddMovementControls(glm::vec3 pos, InputControl* ic)
	{
		movement.push_back(std::make_pair(pos, ic));
	}

	inline void UpdateTransform(Transform& t)
	{
		double frameTime = 1.0 / 60.0;
		double xPos, yPos, zPos;

		for (int i = 0; i < movement.size(); i++)
		{
			xPos = t.GetPos()->x;
			yPos = t.GetPos()->y;
			zPos = t.GetPos()->z;

			xPos += movement[i].first.x * 10.0 * frameTime * movement[i].second->getAmt();
			t.GetPos()->x = xPos;
			yPos += movement[i].first.y * 10.0 * frameTime * movement[i].second->getAmt();
			t.GetPos()->y = yPos;
			zPos += movement[i].first.z * 10.0 * frameTime * movement[i].second->getAmt();
			t.GetPos()->z = zPos;
		}
	}

private:
	std::vector<std::pair<glm::vec3, InputControl*>> movement;
};

