#pragma once
#include "Mesh.h"
#include "Player.h"
#include "ObjectModel.h"
class SpaceObject :
	public ObjectModel
{
public:
	SpaceObject();
	~SpaceObject();

	virtual bool Update(float deltatime);
	virtual bool Draw(glm::mat4 Projection, glm::mat4 View);

	void UpdateShaders(glm::mat4 Projection, glm::mat4 View);
	float MOS(); //mean orbital speed 
	float NLOG(); //newton law of gravity

	Mesh* theSpaceMesh = new Mesh();

	void SetType(int i) { type = i; }
	int GetType() { return type; }

	glm::vec3 GetSunPosition() { return positionSun; }

	void RotatePlanet(float deltatime);
	void RotatePlanetSpace(float deltatime);

	float GetMassPlanet();

	void SetMassPlanet(float themass);

	float GetSunMass();

private:

	const float sunMass = 19890.f;
	const glm::vec3 positionSun = glm::vec3(1);

	Player* thePlayerPointerSpaceObject = nullptr;

protected:



	glm::vec3 momentum;
	glm::vec3 orbitSpeed;
	glm::vec3 orbit;
	glm::vec3 velocity = glm::vec3(1);

	float finalVelocity = 0;
	float radius = 0;
	//float MassObject = 1000;
	const float GravitationalConstant = 0.0000667406f;


	//Mesh planetMesh;
};

