#include "Headers/MeshManager.h"

Mesh* MeshManager::LoadMesh(const char* filename)
{
	std::string fileNameString = filename;

	bool alreadyLoaded = false;

	for (int i = 0; i < filenames.size(); i++)
	{
		if (fileNameString.compare(filenames.at(i)) == 0)
		{
			alreadyLoaded = true;

		}
	}

	int temp = CheckForDouble(fileNameString);

	if (temp != -1)  return &theMeshInGame.at(temp);	//return false;

	if (alreadyLoaded == false)
	{
		float bmin[3];
		float bmax[3];

		//localMesh.LoadObjAndConvert(bmin, bmax, filename);
		return &localMesh;
	}


	//return true;
}

int MeshManager::CheckForDouble(std::string fileNameString)
{

	if (texturManager.find(fileNameString) == texturManager.end())
	{
		//	return texturManager.at(fileNameString);
		return texturManager.count(fileNameString);
	}

	return -1;
}

MeshManager::MeshManager()
{

}

MeshManager::~MeshManager()
{

}

