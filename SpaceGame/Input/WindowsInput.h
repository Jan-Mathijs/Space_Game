#pragma once

#ifndef RASPBERRY
#include "Input/BaseInput.h"
#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include <GLFW/glfw3.h>
//#include "Externals/GLFW/include/glfw3.h"

class WindowsInput :
	public BaseInput
{
public:
	WindowsInput(){}
	WindowsInput(GLFWwindow* window);
	~WindowsInput(){}

//	void CheckInput(GLFWwindow* theInputWindow);
	//void CheckInput(GLFWwindow* theInputWindow);
	void CheckInput();
	//void SetWindowInput(GLFWwindow* theInputWindow) { window = theInputWindow; }
private:
	GLFWwindow* window;
};

#endif