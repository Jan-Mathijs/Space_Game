#pragma once
#ifdef RASPBERRY
#include "BaseWindow.h"
#include "Input/BaseInput.h"


#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <chrono>


#include "bcm_host.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

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
//#ifndef RASPBERRY
//#include  <X11/Xatom.h>
//#include  <X11/Xutil.h>

//#endif //RASPBERRY

//most standard OGL demos use int versions of TRUE and FALSE (careful not to mix up with bool true and false)
#define TRUE 1
#define FALSE 0

//ObjectDate is a small container struct that provides info for render of an object
typedef struct
{
	// save a Handle to a program object
	GLuint programObject;
	// Attribute locations in that shader
	GLint  positionLoc;  // these are common to almost all shaders
	GLint  texCoordLoc;
	GLint samplerLoc;  	// Sampler location
	// Texture handle
	GLuint textureId;  // assuming the texture is in gpu ram here's its ID

} ObjectData;

// general info on the state of the EGL/DispmanX/X11 screen
typedef struct Target_State
{
	uint32_t width;
	uint32_t height;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	// slight difference in the kind of window needed for X11 and Rpi	

	EGL_DISPMANX_WINDOW_T nativewindow;


	ObjectData* object_data;

} Target_State;

// define what kind of EGL config we want, we can add more options but the more we add the less likely it might be available across systems
static const EGLint attribute_list[] =
{
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_ALPHA_SIZE, 8,
	EGL_DEPTH_SIZE,
	8,
	EGL_SURFACE_TYPE,
	EGL_WINDOW_BIT,
	EGL_CONFORMANT,
	EGL_OPENGL_ES2_BIT,

	//be aware, some emulated Mesa OpenGLES2.0 drivers, can choke on these two lines	
	EGL_SAMPLE_BUFFERS,
	 1,
	 // if you want anti alias at a slight fps cost
   EGL_SAMPLES,
	4,
	//keep these 2lines, especially useful for lower resolution

 EGL_NONE
};


static const EGLint context_attributes[] =
{
	EGL_CONTEXT_CLIENT_VERSION, 2,
	EGL_NONE
};
class ARMWindow :
	public BaseWindow
{
public:
	ARMWindow();
	~ARMWindow();
	
	int Init(const unsigned int width, const unsigned int height);
	void SwapBuffer();
	void SetRes(unsigned int& screenX, unsigned int& screenY){}
	//void GetRes(unsigned int& retrunX, unsigned int& returnY);
	//void RestoreRes();

	void MakeWindowClose(const bool val){}
	bool WindowClose(){}

	BaseInput* PrepareInput();

	Display* x_display;
	Window                  win;
	
	void init_ogl(Target_State*, int width, int height, int, int);
	void esInitContext(Target_State*);

	void SetRes(int index, uint32_t& screenX, uint32_t& screenY);
	void GetRes(uint32_t& ReturnX, uint32_t& ReturnY);
	void RestoreRes();
	
	// we provide a simple Texture loader/store syste	
	GLuint CreateSimpleTexture2D(int width, int height, char* TheData);

	GLuint LoadShader(GLenum type, const char* shaderSrc);
	// info needed for X11 screen info, not all used initally.
	short                   original_rate;
	Rotation                original_rotation;
	SizeID                  original_size_id;

	XRRScreenSize* xrrs;
	XRRScreenConfiguration* conf;

	// when we start up we could use the current mouse cursor point to start our own cursor, though X11 can always interrogate it
	int CursorStartPointX;
	int CursorStartPointY;
	// we can store all the possible resolutions here		
	short                   possible_frequencies[64][64]; // a big list of details
	int     num_rates; // how many possible rates
	int		num_sizes; // how many possible sizes

	Target_State state;
	Target_State* p_state = &state;
};

#endif