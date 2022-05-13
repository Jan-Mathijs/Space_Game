#include "Headers/Planet.h"
//test
Planet::Planet(Shader* shader, float radiusplanet, glm::vec3 position, int thetype, float mass)
{
	radius = radiusplanet;
	TheShader = shader;
	theTransform.SetPosition(position);
	type = thetype;
	MassObject = mass;
	theTransform.SetScale(radius * theTransform.GetScale());
	theTransform.SetEulerAngles(glm::vec3(0));
	orbitSpeed.x = static_cast<float>(rand() % 100 + 1) / 600;
	orbitSpeed.y = static_cast<float>(rand() % 100 + 1) / 600;
	orbitSpeed.z = static_cast<float>(rand() % 100 + 1) / 600;

	if (type != -1 || type != 1) {
		velocity = glm::vec3(0, 0, 1) * static_cast<float>(MOS());
	}
}

Planet::Planet(float radiusplanet, glm::vec3 pos, int thetype)
{
	theTransform.SetScale(radiusplanet * theTransform.GetScale());
	theTransform.SetPosition(pos);// = pos;
	type = thetype;
}
