#include "Screen/ARMWindow.h"

#ifdef RASPBERRY
ARMWindow::ARMWindow()
{
	widthScreen = 1920;
	heightScreen = 1080;

	Init(widthScreen, heightScreen);
}

ARMWindow::~ARMWindow()
{
	
}

int ARMWindow::Init(const unsigned width, const unsigned height)
{
	widthScreen = width;
	heightScreen = height;

	esInitContext(p_state);
	init_ogl(p_state, widthScreen, heightScreen, widthScreen, heightScreen);

	ObjectData object_data; // create a single instance of object_data to initially draw all objects with the same data.

	p_state->object_data = &object_data;
}

void ARMWindow::SwapBuffer()
{
	eglSwapBuffers(p_state->display, p_state->surface);
}

// moving initialisaiton and processing to here


void ARMWindow::esInitContext(Target_State* p_state)
{
	if (p_state != NULL)
	{
		memset(p_state, 0, sizeof(Target_State));
	}
}

/*
Set up the EGL and in the case of Raspberry, DispmanX
Set up OpenGL states needed
Also set up the X11 window for rendering on non Taspberry (also used for Gui cursor use on Raspberry)
*/
#ifdef RASPBERRY // do the raspberry set up

void ARMWindow::init_ogl(Target_State* state, int width, int height, int fbx, int fby)
{
	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;


	//RPI setup is a little different to normal EGL
	DISPMANX_ELEMENT_HANDLE_T DispmanElementH;
	DISPMANX_DISPLAY_HANDLE_T DispmanDisplayH;
	DISPMANX_UPDATE_HANDLE_T DispmanUpdateH;
	VC_RECT_T dest_rect;
	VC_RECT_T src_rect;
	EGLConfig config;

	// we also need an xwindow
	Window root;
	XSetWindowAttributes swa;
	XSetWindowAttributes  xattr;
	Atom wm_state;
	XWMHints hints;
	XEvent xev;



	swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask | KeyReleaseMask;
	swa.background_pixmap = None;
	swa.background_pixel = 0;
	swa.border_pixel = 0;
	swa.override_redirect = true;

	/*
	 * X11 native display initialization
	 */

	x_display = XOpenDisplay(NULL);
	if (x_display == NULL)
	{
		printf("Sorry to say we can't create an Xwindow and this will fail");
		exit(0);      // we need to trap this;
	}
	else
		printf("we got an xdisplay\n");


	root = DefaultRootWindow(x_display);

	win = XCreateWindow(
		x_display,
		root,
		0,		// puts it at the top left of the screen
		0,
		width,		//set size  
		height,
		0,
		CopyFromParent,
		InputOutput,
		CopyFromParent,
		CWEventMask,
		&swa);

	if (win == 0)
	{
		printf("Sorry to say we can't create a window and this will fail\n");
		exit(0);       // we need to trap this;
	}
	else
		printf("we got an (Native) XWindow\n");


	bcm_host_init();   //RPI needs this

	// get an EGL display connection
	state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	// initialize the EGL display connection
	result = eglInitialize(state->display, NULL, NULL);

	// get an appropriate EGL frame buffer configuration
	result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
	assert(EGL_FALSE != result);

	// get an appropriate EGL frame buffer configuration
	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);

	// create an EGL rendering context
	state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);
	assert(state->context != EGL_NO_CONTEXT);
	if (state->context != EGL_NO_CONTEXT)
	{
		printf("Hey");
	}

	// create an EGL window surface

	state->width = width;
	state->height = height;

	dest_rect.x = 0;
	dest_rect.y = 0;
	dest_rect.width = state->width;  // it needs to know our window size
	dest_rect.height = state->height;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = 0;
	src_rect.height = 0;

	DispmanDisplayH = vc_dispmanx_display_open(0);
	DispmanUpdateH = vc_dispmanx_update_start(0);

	DispmanElementH = vc_dispmanx_element_add(
		DispmanUpdateH,
		DispmanDisplayH,
		0/*layer*/,
		&dest_rect,
		0/*source*/,
		&src_rect,
		DISPMANX_PROTECTION_NONE,
		0 /*alpha value*/,
		0/*clamp*/,
		(DISPMANX_TRANSFORM_T)0/*transform*/);

	state->nativewindow.element = DispmanElementH;
	state->nativewindow.width = state->width;
	state->nativewindow.height = state->height;
	vc_dispmanx_update_submit_sync(DispmanUpdateH);

	state->surface = eglCreateWindowSurface(state->display, config, &(state->nativewindow), NULL);
	assert(state->surface != EGL_NO_SURFACE);

	// connect the context to the surface
	result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
	assert(EGL_FALSE != result);

	//2 is for 30 fps
	//3 is for 20 fps
	//4 is for 15 fps
	//0.1 is 80 fps
	EGLBoolean test = eglSwapInterval(state->display, 1);         // 1 to lock speed to 60fps (assuming we are able to maintain it), 0 for immediate swap (may cause tearing) which will indicate actual frame rate

		// Some OpenGLES2.0 states that we might need
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(TRUE);
	glDepthRangef(0.0f, 1.0f);
	glClearDepthf(1.0f);

	//these are the options you can have for the depth, play with them?
	//#define GL_NEVER                          0x0200
	//#define GL_LESS                           0x0201
	//#define GL_EQUAL                          0x0202
	//#define GL_LEQUAL                         0x0203
	//#define GL_GREATER                        0x0204
	//#define GL_NOTEQUAL                       0x0205
	//#define GL_GEQUAL                         0x0206

	glViewport(0, 0, state->width, state->height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	if (glGetError() == GL_NO_ERROR)	return;
	else
		printf("Oh bugger, Some part of the EGL/OGL graphic init failed\n");


}
#endif // RASPBERRY



/*
 Now we have be able to create a shader object, pass the shader source
 and them compile the shader.
*/
GLuint ARMWindow::LoadShader(GLenum type, const char* shaderSrc)
{
	// 1st create the shader object
	GLuint TheShader = glCreateShader(type);

	if (TheShader == 0) return FALSE; // can't allocate so stop.

// pass the shader source then compile it
	glShaderSource(TheShader, 1, &shaderSrc, NULL);
	glCompileShader(TheShader);

	GLint  IsItCompiled;

	// After the compile we need to check the status and report any errors
	glGetShaderiv(TheShader, GL_COMPILE_STATUS, &IsItCompiled);
	if (!IsItCompiled)
	{
		GLint RetinfoLen = 0;
		glGetShaderiv(TheShader, GL_INFO_LOG_LENGTH, &RetinfoLen);
		if (RetinfoLen > 1)
		{
			// standard output for errors
			char* infoLog = (char*)malloc(sizeof(char) * RetinfoLen);
			glGetShaderInfoLog(TheShader, RetinfoLen, NULL, infoLog);
			fprintf(stderr, "Error compiling this shader:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteShader(TheShader);
		return FALSE;
	}
	return TheShader;
}



/*
Initialise an object so that it uses the correct shader to display
return int TRUE if all good.
*/

///
// Create a simple width x height texture image with RGBA format
//
GLuint ARMWindow::CreateSimpleTexture2D(int width, int height, char* TheData)
{
	// Texture object handle
	GLuint textureId;

	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		TheData);

	if (glGetError() != GL_NO_ERROR) printf("Oh bugger");

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	if (glGetError() == GL_NO_ERROR)	return textureId;
	printf("Oh bugger");

	return textureId;
}




void ARMWindow::GetRes(uint32_t& ReturnX, uint32_t& ReturnY)
{

	//#ifdef RASPBERRY // raspberry dosn't really work well with xrandr.. so we simply return our current user set res
	//	uint32_t width;
	//	uint32_t height;
	//	ARMWindow_get_display_size(0, &width, &height);
	//		
	//	ReturnX =  width;
	//	ReturnY  = height;
	//	
	//#endif

		// you will need to make sure you have  installed libXrandr to use this..
		//xhisudo apt-get install libxrandr-dev

		//
		//     CONNECT TO X-SERVER, GET ROOT WINDOW ID
		//
		//
		//     GET POSSIBLE SCREEN RESOLUTIONS
		//
	xrrs = XRRSizes(x_display, 0, &num_sizes);
	//
	//     LOOP THROUGH ALL POSSIBLE RESOLUTIONS,
	//     GETTING THE SELECTABLE DISPLAY FREQUENCIES
	//


	for (int i = 0; i < num_sizes; i++) {
		short* rates;


		printf("\n\t%2i : %4i x %4i   (%4imm x%4imm ) ", i, xrrs[i].width, xrrs[i].height, xrrs[i].mwidth, xrrs[i].mheight);

		rates = XRRRates(x_display, 0, i, &num_rates);

		for (int j = 0; j < num_rates; j++) {
			possible_frequencies[i][j] = rates[j];
			printf("%4i ", rates[j]);
		}
	}

	printf("\n");


}
void ARMWindow::SetRes(int index, uint32_t& screenX, uint32_t& screenY)
{
	//
	//     Set RESOLUTION AND FREQUENCY
	//
	GetRes(screenX, screenY); // check what we have
// store the original info for and end
	conf = XRRGetScreenInfo(x_display, DefaultRootWindow(x_display));
	original_rate = XRRConfigCurrentRate(conf);
	original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);

	printf("\n\tCURRENT SIZE ID  : %i\n", original_size_id);
	printf("\tCURRENT ROTATION : %i \n", original_rotation);
	printf("\tCURRENT RATE     : %i Hz\n\n", original_rate);
	// find 1280x720		

		//
	int SelectedRes = index;  // pretty much any system can handle 1024x768 
	printf("\tCHANGED TO %i x %i PIXELS, %i Hz\n\n", xrrs[SelectedRes].width, xrrs[SelectedRes].height, possible_frequencies[SelectedRes][0]);
	XRRSetScreenConfigAndRate(x_display, conf, DefaultRootWindow(x_display), SelectedRes, RR_Rotate_0, possible_frequencies[SelectedRes][0], CurrentTime);
	screenX = xrrs[SelectedRes].width;
	screenY = xrrs[SelectedRes].height;
}

void ARMWindow::RestoreRes()
{
	printf("\tRESTORING %i x %i PIXELS, %i Hz\n\n", xrrs[original_size_id].width, xrrs[original_size_id].height, original_rate);
	XRRSetScreenConfigAndRate(x_display, conf, DefaultRootWindow(x_display), original_size_id, original_rotation, original_rate, CurrentTime);

}


#endif 