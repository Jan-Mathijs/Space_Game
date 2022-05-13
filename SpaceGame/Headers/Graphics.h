#pragma once

// Graphics class primary responsibility is to set up OpenGLES for render and to hold info on X11 window
#include <stdio.h>
#include <assert.h>
#include <math.h>
//#include <sys/time.h>

#ifdef RASPBERRY
#include "bcm_host.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif


#include <vector>
// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Headers/ObjectModel.h"
#include "Headers/ImgGuiUI.h" //our own ui class

// if we use imgui we are going to need these
//#include <X11/Xlib.h> // we now include X11 for all systems including early Rpi's so we can get access to an Xwindow cursor, but only Rpi4>> uses X11 for render
//#include <X11/extensions/Xrandr.h> //this is used for our resolution systems, which are handled a little different on early Rpi's,we still need some of the info, but Rpi res data will be invalid

// these defines are used often (and Pi is a joke :D) 
#define PI	3.14159265358979323846264338327950288419716939937510582097494459072381640628620899862803482534211706798f
#define DEG2RAD(x) (x*PI)/180
#define RAD2DEG(x) x*(180/PI)

// these are more focused on X11 for display so we don't need to include them on a Raspbery, the Xlib and XrandR gives us all the Raspberry needs
#ifdef RASPBERRY
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>

#endif //RASPBERRY

//most standard OGL demos use int versions of TRUE and FALSE (careful not to mix up with bool true and false)
#define TRUE 1
#define FALSE 0

class Graphics
{
public:
	Graphics();
	~Graphics();
	int Init(ObjectModel*);
};