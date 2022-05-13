
#include "Headers/ImgGuiUI.h"

#ifdef RASPBERRY
#include <X11/Xlib.h> 
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif
#undef countof
#include "glm/glm.hpp"
#undef countof



ImgGuiUI::ImgGuiUI()
{
}

ImgGuiUI::~ImgGuiUI()
{
}

bool ImgGuiUI::Init(Input* Input)
{
	// imgui setup
	const char* glsl_version = "#version 100";
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init(glsl_version);
	TheInputHandler = Input;
	
// it once	
	ImGui::SetNextWindowPos(ImVec2(200, 200));
	ImGui::SetNextWindowSize(ImVec2(400, 24 * 4));
	
	return true;	
}
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

bool ImgGuiUI::Update(bool DoINeedTo, float DT)
{
	if (!DoINeedTo) return true; // if not updating there is no error so just return true
	

	//Window window_returned;
	
	//int root_x;
	//int root_y;
	//int win_x;
	//int win_y;
	//uint mask_return;
	
	// be aware, this returns the pointer based on screen res, if using a raspberry you need to adjust to Frame buffer res
	//bool result = XQueryPointer(
	//	x_display,
	//	win,
	///	&window_returned,
	//	&window_returned,
		
	//	&root_x,
	//	&root_y,
	//	&win_x,
	//	&win_y,
	//	&mask_return);
	
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(1920, 1080); // window size, NOT resolution, this is important
	io.DeltaTime = DT;
	// we should also pass on mouse and key info into the IO here
	
	io.MousePos = ImVec2(TheInputHandler->TheMouse.PositionX, TheInputHandler->TheMouse.PositionY);
	io.MouseDown[0] = TheInputHandler->TheMouse.LeftButton;// &(1 << 8); // left
	io.MouseDown[1] = TheInputHandler->TheMouse.RightButton;// & (1 << 10); // right
	io.MouseDrawCursor = true;
	
	// get on with the text/windows	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();   // do this at the start of any frame
	io.WantCaptureMouse = true;
	
	ImGui::SetNextWindowBgAlpha(0);
	// make sure you begin by naming the window		
	ImGui::Begin("Useful GPU Info");
	
	
	// its useful to know what your resolution options are.		
/*	if (ImGui::TreeNode("Resolutions Available"))
	{
	
		char buf[128];	
		// send text or buttons or sliders or whatver
		for(int i = 0 ; i < WhereIsTheGraphicClass->num_sizes ; i++)
		{
		
			sprintf(buf, "\t%2i : %4i x %4i :(%4imm x%4imm )", i, WhereIsTheGraphicClass->xrrs[i].width, WhereIsTheGraphicClass->xrrs[i].height, WhereIsTheGraphicClass->xrrs[i].mwidth, WhereIsTheGraphicClass->xrrs[i].mheight);
			ImGui::Text("%s",buf); // the "%s", formats it to st
		}
		ImGui::TreePop();
	}*/
// lets print up something cool	
	/*if (ImGui::TreeNode("Extensions Possible"))
	{
		char buf[10000];	// needs to point to some chars, make it quite big cos we really have no idea how big the string will be	
		sprintf(buf,"%s\n", glGetString(GL_EXTENSIONS)); // get the extension "string" (its really a char array so sprintf converts it to a string and stores in our big buffer
		istringstream iss(buf); // make a stream out of it
		do // lets parse over the string and strip the space divided text out
		{
			string substring; // somewhere to hold the substring
			iss >> substring; // pipe it in.
			ImGui::Text("%s", substring.c_str()); // imgui needs a const char* again so a bit of reformatting needed

		} while (iss);
		
		ImGui::TreePop();
	} */// and now we're out of scope that big buffer barnacle bids bye bye

	
	
	ImGui::End(); 
	return true;  // we're not likely to do much that needs a false condition but pass a variable if you prefer

}
	
bool ImgGuiUI::Render(bool DoINeedTo)
{
	if (!DoINeedTo) return true; // if not updating there is no error so just return true
	
		ImGui::Render();
	// and finally render to the GPU	
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	GLint err = glGetError(); // this is just a sanity check, can be removed(and it is quite slow)
	return err == FALSE; // remember GL returns int values, we ned to return bool
}
