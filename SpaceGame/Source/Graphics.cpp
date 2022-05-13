#include "../Headers/Graphics.h"


Graphics::Graphics()
{

}
Graphics::~Graphics()
{

}

int Graphics::Init(ObjectModel* TheModel)
{
	// Get the attribute locations
	TheModel->positionLoc = glGetAttribLocation(TheModel->TheShader->ID, "a_position");
	TheModel->texCoordLoc = glGetAttribLocation(TheModel->TheShader->ID, "a_texCoord");
	TheModel->normLoc = glGetAttribLocation(TheModel->TheShader->ID, "a_normal");

	// Get the sampler location
	TheModel->samplerLoc = glGetUniformLocation(TheModel->TheShader->ID, "s_texture");

	int error = 0;
	if (error = glGetError() == GL_NO_ERROR)	return TRUE;
	else
		printf("Oh bugger, Model graphic init failed %i\n", error);
	return FALSE;

}


