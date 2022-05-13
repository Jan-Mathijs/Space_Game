#pragma once
#include "Headers/Scene.h"
#include "Headers/ObjectModel.h"
#include "Headers/MyFiles.h"
#include "Headers/Graphics.h"
#include "Headers/SpaceObject.h"
#include "Headers/Planet.h"
#include "Headers/SkyBox.h"
#include "Headers/SpaceStation.h"
#include "Headers/SpaceInterior.h"
#include "Headers/SceneSpace.h"
#include "Headers/SceneWorld.h"
#include "Headers/GroundPlane.h"
//#include "Headers/PlayerWorld.h"
//#include "Headers/PlayerSpace.h"

#include <stdio.h>
#ifdef RASPBERRY
#include <unistd.h>
#define GetCurrentDir getcwd
#include "Input/LinuxInput.h"
#else
#include <direct.h>
#define GetCurrentDir _getcwd
#include "Input/WindowsInput.h"
#endif


#include <iostream>

class WorldManager
{
private:
	Scene* activeScene = nullptr;
	Scene* scenes[3]; //at the moment only one scene
public:

	WorldManager() {}
	WorldManager(std::vector<Mesh::DrawObject>& modelVector, Graphics& grap, std::vector<ObjectModel*> MyObjects);
	~WorldManager();

	void CurrentScene(const int index) {}
	Scene* GetActiveScene();
	void MakeScene();

	void updateWorldManager(float deltaTime);
	void PrepareScenes();
	void SetCurrentScene(Scene* theScene);

	Shader GetShader();
	void SetShader(Shader& theShaders);

	void SetBoundingBox(ObjectModel* objmodel, float min[3], float max[3]);
	Shader theShader;

	std::string PathHandler(std::string directory, std::string name);

	static std::string GetCurrentWorkingDir();

	bool nextScene = false;
#ifdef RASPBERRY
	LinuxInput* theInputWorldManager;
#else
	WindowsInput* theInputWorldManager;
#endif
private:

	std::vector<Mesh::DrawObject> manager;
	std::vector<ObjectModel*> myObjects;
	std::vector<tinyobj::material_t> material;
	std::map<std::string, GLuint> textures;
	std::vector<Shader> shaders;

	MyFiles* Handler = new MyFiles();

	Graphics graphicsPtr;

	float scalerDistance = 25.f;

	float waitTime = 0;
	float minWaitTime = 5.0f;
};

