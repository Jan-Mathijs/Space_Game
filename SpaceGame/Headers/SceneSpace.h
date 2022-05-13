#pragma once
#include "Headers/Scene.h"
class SceneSpace :
	public Scene
{
public:
	SceneSpace();
	~SceneSpace();

	void CheckIntersectionsSceneSpace(bool& nextScene, float deltaTime);

	void Update(float deltatime, glm::mat4 projection, glm::mat4 view, bool& nextScene) override;

private:
	float timeWaint = 0;
	float minTimeWait = 5.0f;
};

