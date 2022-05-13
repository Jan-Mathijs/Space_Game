#include <stdio.h>
#include <assert.h>
#include <math.h>
//#include <sys/time.h>

#ifdef RASPBERRY
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#else
#define GLFW_INCLUDE_NONE
#define NOMINMAX
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif
#include <vector>

#include <stdio.h>
#include <assert.h>
#include <math.h>
//#include <sys/time.h>

#include <chrono>

#ifdef RASPBERRY
#include "bcm_host.h"
#include "Input/LinuxInput.h"
#include "Screen/ARMWindow.h"
//#include <EGL/egl.h>
//#include <EGL/eglext.h>
ARMWindow* theWindow = new ARMWindow();
LinuxInput* theInputHello = new LinuxInput();

//#include <GLES2/gl2.h>
#else
#include "Screen/dirXWindow.h"
#include "Input/WindowsInput.h"
dirXWindow* theWindow = new dirXWindow();
WindowsInput* theInputHello = new WindowsInput(theWindow->GetWindow());
#endif


#include <vector>
// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Headers/Graphics.h"
#include "Headers/ObjectModel.h"

#include "Headers/Mesh.h"
#include "Headers/Player.h"
#include "Headers/Camera.h"
#include "Headers/WorldManager.h"


using namespace glm;

std::vector<ObjectModel*> MyObjects;
Graphics graphics_Ptr;  // create a 1 time instance of a graphics class in Global space

Player* thePlayer = new Player();
Camera* theCamera = new Camera(thePlayer->theTransform.GetPosition() + glm::vec3(0,0,-15),glm::vec3(0,1,0));
WorldManager* theWorldManager = new WorldManager();

glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);


glm::mat4 View = glm::lookAt(
	glm::vec3(0, 0, 0),	 
	glm::vec3(0, 0, 0),		 
	glm::vec3(0, 1, 0) 	
);
void Update(float deltaTime)
{
 	theWorldManager->GetActiveScene()->GetActiveCamera()->Update(View, deltaTime);

	theWorldManager->updateWorldManager(deltaTime);
	theWorldManager->GetActiveScene()->Update(deltaTime, Projection, View, theWorldManager->nextScene);

}


Input* TheInput; 
ImgGuiUI TheUI;


//projects main  Game loop
void  MainLoop()
{
	
	TheInput = new Input();
	TheInput->Init();
	
	TheUI.Init(TheInput);


#ifdef RASPBERRY
	theInputHello->theInput = TheInput;
#endif
		
	std::chrono::high_resolution_clock timer;
	std::chrono::high_resolution_clock::time_point start = timer.now(), stop;

	
	auto currenttime = std::chrono::steady_clock::now();

	float deltatime;
	float totaltime = 0.0f;
	unsigned int frames = 0;
	

	bool EscapeKeyTrue = false;
	
	int Counter = 0;
	while (theInputHello->inputKeyESC == false) // for a timed loop check the counter otherwise find another exit condition
		{

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			stop = timer.now();
			std::chrono::duration<double> elapsed = stop - start;

			deltatime = elapsed.count();

			
			Update(deltatime);  // this is where the action happens
			
			TheUI.Update(true, deltatime);
		
			TheUI.Render(true);	

			

			totaltime += deltatime;
			frames++;
			if (totaltime >  1.0f)
			{
				printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames / totaltime);  // uncomment to see frames
				totaltime -= 1.0f;
				frames = 0;
			}

#ifdef RASPBERRY
			if (TheInput->Keys[KEY_ESC] == TRUE)
			{
				EscapeKeyTrue = true;

			}
						
#endif
			start = stop;
			
			theWindow->SwapBuffer();

			
		}
}

//Program Entry
int main(int argc, char *argv[])
{

	MyFiles* Handler = new MyFiles();

	uint32_t ReturnX;
	uint32_t ReturnY;

	TheUI.WhereIsTheGraphicClass = &graphics_Ptr;
	
	std::string frag = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/default.frag";
	std::string vertstr = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/default.vert";
	Shader defaultShader(vertstr.c_str(), frag.c_str());
	std::string frag2 = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/diffuse.frag";
	std::string vertstr2 = WorldManager::GetCurrentWorkingDir() + "Resources/Shader/diffuse.vert";
	Shader diffuseShader(vertstr2.c_str(), frag2.c_str());

	theWorldManager->SetShader(defaultShader);
	theWorldManager->SetShader(diffuseShader);
	theWorldManager->theShader = defaultShader;
	theWorldManager->theInputWorldManager = theInputHello;
	theWorldManager->MakeScene();
	
	MainLoop();
	return 0;
}
