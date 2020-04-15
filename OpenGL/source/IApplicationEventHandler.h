#pragma once

class IApplicationEventHandler
{
public:
	IApplicationEventHandler() {}
	virtual ~IApplicationEventHandler() {}
	virtual void onKeyDown(unsigned int keyCode, bool isRepeat) {}
	virtual void onKeyUp(unsigned int keyCode, bool isRepeat) {}
	virtual void onMouseDown(unsigned int mouseButton, unsigned int numClicks) {}
	virtual void onMouseUp(unsigned int mouseButton, unsigned int numClicks) {}
	//virtual void onMouseMove(int32 mousePosX, int32 mousePosY,
		//int32 deltaX, int32 deltaY) {}
private:
	void NULL_COPY_AND_ASSIGN(IApplicationEventHandler);
};
