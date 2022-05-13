#pragma once
#include "Headers/ObjectModel.h"
#include "Headers/Mesh.h"
#include "Headers/WorldManager.h"

class WorldManager;
class SkyBox :
	public ObjectModel
{
public:
	SkyBox();
	//SkyBox(Shader* shader, glm::vec3 Position, int thetype, char* filename);
	~SkyBox();
	SkyBox(const char* right, const char* left, const char* top, const char* bottem, const char* front, const char* back, int typeobj);
	bool Update(float deltatime);  
	bool Draw(glm::mat4 Projection, glm::mat4 View);

	void UpdateShaders(glm::mat4 Projection, glm::mat4 View);

	//Mesh* GetMesh() { return theMesh; }
	Mesh* theMesh = new Mesh();
	//void SetMesh(Mesh* theMeshPtr) { theMesh = theMeshPtr; }

	glm::vec3* positionCameraPTR;
private:
	GLuint programObject;

	GLenum  cubeMapTarget[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	   GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	   GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	   GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
	};

	GLuint textureID[16];

	GLuint VBO; 
	char m_cube_map_textures[6][255];
	GLint UVMapUniformLocation;

	
	int imageWidth, imageHeight;
};

