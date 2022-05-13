#pragma once
#include "Headers/ObjectModel.h"
#include "Mesh.h"
#include "PhysicsObj.h"
#include <bullet/btBulletDynamicsCommon.h>

class WorldObject :
	public ObjectModel
{
public:
	WorldObject();
	WorldObject(Shader* shader, int type, float mass);
	~WorldObject();

	virtual bool Update(float deltatime);
	virtual bool Draw(glm::mat4 Projection, glm::mat4 View);

	Mesh* theWorldMesh = new Mesh();

	void UpdateShaders(glm::mat4 Projection, glm::mat4 View);
	
	
	PhysicsObj* MyPhysObj = nullptr;


private:

	PhysicsObj* theWorldPhysicsObj = nullptr;
	float ObjectMass = 500;

	glm::vec4 Amb = glm::vec4(1.0f);

};

