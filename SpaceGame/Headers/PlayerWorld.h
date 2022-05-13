#pragma once
#include "Player.h"
class PlayerWorld :
	public Player
{
	PlayerWorld(Shader* theShader, int type);

	bool Update(float deltatime);

	void	HandleCollision(ObjectModel*);
};

