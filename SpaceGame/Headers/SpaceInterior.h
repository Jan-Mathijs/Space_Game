#pragma once
#include "Headers/WorldObject.h"
class SpaceInterior :
	public WorldObject
{
public:
	SpaceInterior(Shader* shader, glm::vec3 position, int type);
	~SpaceInterior();

	//bool Update(float deltatime);

};

