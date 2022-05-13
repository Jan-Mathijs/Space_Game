#pragma once

#define TRUE 1
#define FASLE 0
class BaseWindow
{
protected:
	unsigned int widthScreen = 0;
	unsigned int heightScreen = 0;
public:
	BaseWindow(){}
	~BaseWindow(){}
	virtual int Init(const unsigned int width, const unsigned int height) = 0;
	virtual void SwapBuffer() = 0;
	virtual void SetRes(unsigned int& screenX, unsigned int& screenY) = 0;
	virtual void GetRes(unsigned int& retrunX, unsigned int& returnY) = 0;
	virtual void RestoreRes() = 0;

	virtual void MakeWindowClose(const bool val) = 0;
	virtual bool WindowClose() = 0;

	unsigned int GetWidth() const {return widthScreen; }
	unsigned int GetHeight() const { return heightScreen; }
	
};

