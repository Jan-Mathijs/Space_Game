#pragma once
#include "SpaceObject.h"
#include "random"
class Planet :
	public SpaceObject
{
public:
	Planet(float radius, glm::vec3 Pos, int type);
	Planet(Shader* shader, float radiusplanet, glm::vec3 position, int type, float mass);
	~Planet() {}

private:
};

