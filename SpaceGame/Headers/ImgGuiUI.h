#pragma once

// Image GUI UI is a practical UI interface we can use to provide an interacive UI for game related values
// its not especially useful for in game use but can be adapeted. Its main advantage is the ability to alter and display variables
// and system info during game set up or mode changes

#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "Input.h"
#include <iostream>
#include <algorithm>
#ifdef RASPBERRY
#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>
#include   <X11/extensions/Xrandr.h>

#endif
#include "Headers/Graphics.h" // included as it has the resolution data we can use for displa


#ifdef	RASPBERRY
extern  Display* x_display; // actually in the graphics class but exposed to global space
extern  Window win;

extern	XRRScreenSize           *xrrs;    // this will contain the resolution values
#endif

extern int num_sizes;


class ImgGuiUI
{
public:
	ImgGuiUI();
	~ImgGuiUI();
// maybe we can keep a list of different windows and display them in turn or in order	
//	std::vector<> List?;
	
	bool Init(Input* TheInputHandler);
	bool Remove()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
		return true;
	}; // if we are done with UI (after an initial set up), lets remove it
	bool Update(bool DoINeedTo, float DT);
	
	bool Render(bool DoINeedTo);
	
	Graphics* WhereIsTheGraphicClass;
	
	Input* TheInputHandler; // this will be needed
}
;


