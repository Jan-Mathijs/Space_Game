#ifndef RASPBERRY
#include "dirXWindow.h"


dirXWindow::dirXWindow()
{
	widthScreen = 1920;
	heightScreen = 1080;
	Init(widthScreen, heightScreen);
}

dirXWindow::~dirXWindow()
{
	if (window != 0)
		glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
int dirXWindow::Init(const unsigned int width, const unsigned int height)
{
	widthScreen = width;
	heightScreen = height;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	
	window = glfwCreateWindow(widthScreen, heightScreen, "SpaceGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(TRUE);
	glDepthRangef(0.0f, 1.0f);
	glClearDepthf(1.0f);

	glViewport(0, 0, (uint32_t)width, (uint32_t)height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	return 0;
}

void dirXWindow::SwapBuffer()
{
	glfwSwapBuffers(window);
}

void dirXWindow::GetRes(unsigned& retrunX, unsigned& returnY)
{
	retrunX = widthScreen;
	returnY = heightScreen;
}

void dirXWindow::SetRes(unsigned& screenX, unsigned& screenY)
{
	widthScreen = screenX;
	heightScreen = screenY;
}



void dirXWindow::MakeWindowClose(const bool val)
{
	glfwWindowShouldClose(window);
	WindowClose();
}

bool dirXWindow::WindowClose()
{
	glfwTerminate();
	return 0;
}

#endif