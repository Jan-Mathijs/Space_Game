#pragma once
#include "ObjectModel.h"
#include "Camera.h"
#include "Player.h"


class Scene
{
public:
	Scene();
	~Scene();

	virtual void SetCameraScene(Camera* theCamera);

	virtual void SetPlayerScene(Player* playerScene);
	
	virtual void Update(float deltattime, glm::mat4 projection, glm::mat4 view, bool& nextScene) = 0;
	virtual Camera* GetActiveCamera();
	virtual Player* GetActivePlayer();
	
	std::vector<ObjectModel*> meshVector;
	std::vector<Shader> sceneShaders;

	void SetFirstCall(bool value) { firstCall = value; }
private:
	
	Camera* theCameraInScene = nullptr;
	Player* thePlayerInScene = nullptr;
protected:
	bool firstCall = false;
};

