#pragma once
#include "Headers/Scene.h"
#include "Headers/PhysicsObj.h"
#include <set>
#include <iterator>

//#include <bullet/btBulletDynamicsCommon.h>

class SceneWorld :
	public Scene
{
public:
	SceneWorld();
	~SceneWorld();

	void Update(float deltatime, glm::mat4 projection, glm::mat4 view, bool& nextScene) override;

	void CheckForCollision();

	void CollisionEvent(btRigidBody* RB0, btRigidBody* RB1);

	void SeparationEvent(btRigidBody* RB0, btRigidBody* RB1);

	void SetLocalShaders(Shader* shader1, Shader* shader2);

	btDiscreteDynamicsWorld* GetPhysicsWorld();

	btBroadphaseInterface* BroadPhase;
	btDefaultCollisionConfiguration* CollisionConfiguration;
	btCollisionDispatcher* Dispatcher;
	btSequentialImpulseConstraintSolver* ConstraintSolver;
	btDiscreteDynamicsWorld* DynamicPhysicsWorld;

	PhysicsObj* CreatePhysicsObj(btCollisionShape* pShape,
		const float& mass,
		const btVector3& Position = btVector3(0, 0, 0),
		const btQuaternion& Rotation = btQuaternion(0, 0, 0, 1));

	PhysicsObj* SetPhysicsObject(ObjectModel* objmodel);

	PhysicsDraw* m_pPhysicsDrawer;

	void SetDebugDrawer(const char* vert, const char* frag);


private:

	void CheckForChangeWorld();
	void CalculateWorldPosForInterection(bool& nextScene);
	void TurnLightOn();

	std::map<std::string, btCollisionShape*> ExistingColShapes;
	typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionObjects;
	typedef std::set<CollisionObjects> ManifoldPairs;
	ManifoldPairs pairsLastFrame;

	Shader* diffuseShader;
	Shader* defaultShader;

	bool turnedLightsOn = false;

};

