
#pragma once


#pragma once
#include "Headers/WorldObject.h"

// simple class mainly here to allow us to control an OBJModel type Object and get its mesh


class Ground : public WorldObject
{
public:
	Ground();
	~Ground();

	//Ground(MyFiles* FH, char* FN, ModelManager* MM);
	Ground(Shader* shader, int type, float mass);

	void Init();
	std::vector<btVector3> CollisionMesh;

	btTriangleMesh* triangleMeshTerrain;

};
