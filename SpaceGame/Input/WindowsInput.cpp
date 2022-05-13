#ifndef  RASPBERRY
#include "WindowsInput.h"

WindowsInput::WindowsInput(GLFWwindow* thewindow) {
	window = thewindow;
}


void WindowsInput::CheckInput()
{
	glfwPollEvents();
	if (window != nullptr) 
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			inputKeyESC = true;
			glfwTerminate();
			
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		{ 
			inputKeyW = true; 
		} else inputKeyW = false;
			

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			inputKeyS = true;
		}
		else inputKeyS = false;

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			inputKeyQ = true;
		}
		else inputKeyQ = false;

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			inputKeyE = true;
		}
		else inputKeyE = false;

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			inputKeyArrowUp = true;
		}
		else inputKeyArrowUp = false;

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			inputKeyArrowDown = true;
		}
		else inputKeyArrowDown = false;

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			inputKeyArrowLeft = true;
		}
		else inputKeyArrowLeft = false;

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			inputKeyArrowRight = true;
		}
		else inputKeyArrowRight = false;

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			inputKeyL = true;
		}
		else inputKeyL = false;

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			inputKeyZ = true;
		}
		else inputKeyZ = false;
	}
	
}
#endif

