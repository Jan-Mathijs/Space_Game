#include "Headers/SpaceInterior.h"

SpaceInterior::SpaceInterior(Shader* shader, glm::vec3 position, int thetype)
{
	TheShader = shader;
	theTransform.SetPosition(position);// = position;
	type = thetype;
}

SpaceInterior::~SpaceInterior()
{

}

/*bool SpaceInterior::Update(float deltaTime)
{

}*/