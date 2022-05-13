#pragma once
#include "Headers/SpaceObject.h"
class SpaceStation :
	public SpaceObject
{
public:
	SpaceStation(Shader* shader, float radiusplanet, glm::vec3 position, int thetype, float mass);
	~SpaceStation();

	bool Update(float deltatime);
private:
};

