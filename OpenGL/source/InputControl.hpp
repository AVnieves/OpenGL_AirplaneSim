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
	//float weight;
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

//inline float InputControl::getWeight()
//{
//	if (weight > 1)
//		weight = 1;
//	else if (weight < -1)
//		weight = -1;
//
//	return weight;
//}
//
//inline void InputControl::setWeight(float w)
//{
//	weight = w;
//}
