#pragma once
#include "Mesh.h" 
class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	Mesh* LoadMesh(const char* filename);
	int CheckForDouble(std::string fileNameString);

	std::vector<Mesh*> meshes;
private:

	int MeshID = 0;
	Mesh localMesh;
	std::vector<std::string> filenames;
	std::map<std::string, GLuint> texturManager;
	std::vector<Mesh> theMeshInGame;
};

