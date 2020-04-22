#pragma once
#include "source/InputControl.hpp"
#include "source/TestEventHandler.hpp"
#include "source/transform.h"
#include "source/camera.h"

class CameraControl
{
public:
	inline CameraControl()
	{

	}

	inline ~CameraControl()
	{

	}

	inline void AddMovementControls(glm::vec3 pos, InputControl* ic)
	{
		movement.push_back(std::make_pair(pos, ic));
	}

	inline void UpdateCamera(Camera& c)
	{
		double frameTime = 1.0 / 60.0;
		double xPos, yPos, zPos;

		for (int i = 0; i < movement.size(); i++)
		{
			xPos = c.GetPos()->x;
			yPos = c.GetPos()->y;
			zPos = c.GetPos()->z;

			xPos += movement[i].first.x * 10.0 * frameTime * movement[i].second->getAmt();
			c.GetPos()->x = xPos;
			yPos += movement[i].first.y * 10.0 * frameTime * movement[i].second->getAmt();
			c.GetPos()->y = yPos;
			zPos += movement[i].first.z * 10.0 * frameTime * movement[i].second->getAmt();
			c.GetPos()->z = zPos;
		}
	}

private:
	std::vector<std::pair<glm::vec3, InputControl*>> movement;
};

