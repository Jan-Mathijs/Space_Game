#ifndef RASPBERRY
#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
//#include "Externals/\GLFW\include/GLFW/"
#include <GLFW/glfw3.h>
//#include <GLFW/glfw3.h>

#include "BaseWindow.h"
#include <iostream>

class dirXWindow: public BaseWindow
{
private:
	GLFWwindow* window;
	//WindowsInput* theInput = new WindowsInput();
public: 
	dirXWindow();
	~dirXWindow();

	int Init(const unsigned int width, const unsigned int height);
	void SwapBuffer();
	void SetRes(unsigned int& screenX, unsigned int& screenY);
	void GetRes(unsigned int& retrunX, unsigned int& returnY);
	void RestoreRes(){}

	void MakeWindowClose(const bool val);
	bool WindowClose();

	GLFWwindow* GetWindow() { return window; }
	
	//BaseInput* PrepareInput();

};

#endif
