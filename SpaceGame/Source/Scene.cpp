#include "Headers/Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::SetCameraScene(Camera* theCamera)
{
	theCameraInScene = theCamera;
}

void Scene::SetPlayerScene(Player* playerScene)
{
	thePlayerInScene = playerScene;
}

Camera* Scene::GetActiveCamera()
{
	return theCameraInScene;
}

Player* Scene::GetActivePlayer()
{
	return thePlayerInScene;
}


