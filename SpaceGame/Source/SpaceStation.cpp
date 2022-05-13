#include "Headers/SpaceStation.h"

SpaceStation::SpaceStation(Shader* shader, float radiusplanet, glm::vec3 position, int thetype, float mass)
{
	radius = radiusplanet;
	TheShader = shader;
	theTransform.SetPosition(position);// = position;
	type = thetype;
	MassObject = mass;

	// Scales = glm::vec3(1);
	// Scales = radius * Scales;
	theTransform.SetScale(radius * theTransform.GetScale());
	//  Rotations = glm::vec3(0);

	BoundingBoxMin = glm::vec3(0);//- glm::vec3(Scales.x /2, Scales.y / 2, Scales.z / 2);
	BoundingBoxMax = glm::vec3(10, 10, 10); //WorldPosition + glm::vec3(Scales.x / 2, Scales.y / 2, Scales.z / 2);
}

SpaceStation::~SpaceStation()
{

}

bool SpaceStation::Update(float deltatime)
{
	//mScaleMatrix = glm::mat4(1.0f);

 //   mScaleMatrix = glm::scale(mScaleMatrix, theTransform.GetScale());

	//CalculateGravatationalForce(this->WorldPosition);


   // MakeRotationMatrix();
	//MakeTranslationMatrix();
   // MakeModelMatrix();
	theTransform.SetRotation(glm::vec3(0));// = glm::vec3(0);

	return true;
}