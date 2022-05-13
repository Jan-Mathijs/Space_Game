// this is only here to create and display the environent

#include "Headers/GroundPlane.h"
#include "Headers/MyFiles.h"


Ground::Ground()
{}

Ground::~Ground()
{}

Ground::Ground(Shader* shader, int typeGround, float mass)
{
	TheShader = shader;
	type = typeGround;
	MassObject = mass;
}

void Ground::Init()
{
	//CollisionMesh.clear(); // were done with this now
	triangleMeshTerrain = new btTriangleMesh(); // make a mesh for the terrain

	for (int i = 0; i < CollisionMesh.size(); i += 3)
	{ // load it up with the vertices from our load systems
		triangleMeshTerrain->addTriangle(CollisionMesh[i], CollisionMesh[i + 1], CollisionMesh[i + 2]);
	}
	mesh = new btBvhTriangleMeshShape(triangleMeshTerrain, true);

	CollisionMesh.clear();
}
