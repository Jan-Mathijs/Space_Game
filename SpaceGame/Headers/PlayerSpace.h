#pragma once
#include "Headers/Player.h"
#include "Shader.h"
class PlayerSpace :
	public Player
{
	PlayerSpace(Shader* theShader, int type);
};

