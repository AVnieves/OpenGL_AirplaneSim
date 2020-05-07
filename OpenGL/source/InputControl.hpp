// Adapted from Bennybox tutorial on Youtube
#pragma once

class InputControl
{
public:
	InputControl();
	void addAmt(float amtToAdd);
	float getAmt();
	void setWeight(float w);
	float getWeight();
	void setAmt(float amtToSet);
private:
	float amt;
};

inline InputControl::InputControl() :
	amt(0.f) {}

inline void InputControl::addAmt(float amtToAdd)
{
	amt += amtToAdd;
}

inline void InputControl::setAmt(float amtToSet)
{
	amt = amtToSet;
}

inline float InputControl::getAmt()
{
	if (amt > 1)
		return 1;
	else if (amt < -1)
		return -1;

	return amt;
}