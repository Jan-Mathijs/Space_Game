#include "Headers/SceneWorld.h"
#include <iostream>
SceneWorld::SceneWorld()
{
	BroadPhase = new btDbvtBroadphase();
	CollisionConfiguration = new btDefaultCollisionConfiguration();
	Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	ConstraintSolver = new btSequentialImpulseConstraintSolver;
	DynamicPhysicsWorld = new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, ConstraintSolver, CollisionConfiguration);
	// set a "normal" gravity level
	DynamicPhysicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

SceneWorld::~SceneWorld()
{

}

void SceneWorld::SetDebugDrawer(const char* vert, const char* frag)
{
	//m_pPhysicsDrawer = new PhysicsDraw();
	//m_pPhysicsDrawer->setDebugMode(1011);
	//Shader* temp = new Shader();
	//GLuint SimpleShader = temp->MakeProgramObject(vert, frag);
	//this->DynamicPhysicsWorld->setDebugDrawer(m_pPhysicsDrawer);
//	sceneShaders;
	//PhysicsDraw::ProgramObject = SimpleShader;
	//m_pPhysicsDrawer->ToggleDebugFlag(1 + 2);
}

void SceneWorld::Update(float deltatime, glm::mat4 projection, glm::mat4 view, bool& nextScene)
{
	DynamicPhysicsWorld->stepSimulation(1 / 60.0f, 5); //the 60.0f has to be a float

	for (int i = 0; i < meshVector.size(); i++)
	{
		//update the object, in this demo, we just up its position and transform data but you should consider logic
		meshVector[i]->Update(deltatime);
		//if(!this->m_pPhysicsDrawer->m_debugMode)
		meshVector[i]->Draw(projection, view);
	}

	if (!firstCall) {
		GetActivePlayer()->thePlayerPhysics->SetPosition(GetActivePlayer()->glmToBullet(GetActivePlayer()->theTransform.GetPosition()));
		firstCall = true;
	}

	CheckForCollision();

	CalculateWorldPosForInterection(nextScene);
}

void SceneWorld::CheckForCollision()
{
	ManifoldPairs pairsThisFrame;

	// go through all the manifolds in the Dispatchers list
	for (int i = 0; i < Dispatcher->getNumManifolds(); i++)
	{
		btPersistentManifold* Manifold = Dispatcher->getManifoldByIndexInternal(i);
		if (Manifold->getNumContacts() > 0) 	// we only care if they have contact points
		{
			//getBodyx actually returns btCollisionObject, and we really need to get btRigidBody instead for compares
			//so we have to use the C++ styly static cast. (or plant an idvalue in the rigid body if they are unique)
			const btRigidBody* Body0 = static_cast<const btRigidBody*>(Manifold->getBody0());
			const btRigidBody* Body1 = static_cast<const btRigidBody*>(Manifold->getBody1());

			// since they are pointers, they have numerical value, use that to store them lowest value first

			const btRigidBody* FirstRB = (Body0 > Body1) ? Body1 : Body0;
			const btRigidBody* SecondRB = (Body0 > Body1) ? Body0 : Body1;
			// create the pair
			CollisionObjects NewPair = std::make_pair(FirstRB, SecondRB);
			// insert the pair into the current list
			pairsThisFrame.insert(NewPair);
			//this pair definitely are colliding, if they are brand new we can safely say its a collsion event
			if (pairsLastFrame.find(NewPair) == pairsLastFrame.end()) // search the old list for this new pair
			{
				CollisionEvent((btRigidBody*)Body0, (btRigidBody*)Body1); // got through to the end...it wasn't there so this is a new hit
			}
		} // if
	} // for i

// create another list for pairs that were removed this update, they will be seperated events
	ManifoldPairs removedPairs;
	// compare the set from lset frame with the	set this frame and put the removed one sin the removed Pairs
	std::set_difference(pairsLastFrame.begin(), pairsLastFrame.end(), pairsThisFrame.begin(), pairsThisFrame.end(), std::inserter(removedPairs, removedPairs.begin()));

	// iterate through all of the removed pairs sending separation events for them, can't use an index for this so this is a C++11 iterer
	for (ManifoldPairs::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); ++iter)
	{
		SeparationEvent((btRigidBody*)iter->first, (btRigidBody*)iter->second);
	}

	// because the names for sets are pointers, we can simply tell the Last pair it is now the current pair
	pairsLastFrame = pairsThisFrame;
}

void SceneWorld::CollisionEvent(btRigidBody* RB0, btRigidBody* RB1)
{
	ObjectModel* First = (ObjectModel*)RB0->getUserPointer(); // assumes we set up the user pointer with an ObjectModel*
	ObjectModel* Second = (ObjectModel*)RB1->getUserPointer(); // and there are handling routines in ObjectModel or overrides in derived
	First->HandleCollision(Second);
	Second->HandleCollision(First);
}

void SceneWorld::SeparationEvent(btRigidBody* RB0, btRigidBody* RB1)
{
	printf("Help I've been seperated sob \n");
}

btDiscreteDynamicsWorld* SceneWorld::GetPhysicsWorld()
{
	if (DynamicPhysicsWorld != nullptr)
	{
		return DynamicPhysicsWorld;
	}

}

PhysicsObj* SceneWorld::SetPhysicsObject(ObjectModel* objmodel)
{
	PhysicsObj* temp;

	if (objmodel->MassObject == 0)
	{
		temp = CreatePhysicsObj(objmodel->mesh, objmodel->MassObject,
			btVector3(objmodel->theTransform.GetPosition().x, objmodel->theTransform.GetPosition().y, objmodel->theTransform.GetPosition().z));
	}
	else if (objmodel->type == 5)
	{
		btScalar radius = (objmodel->BoundingBoxMin.x - objmodel->BoundingBoxMax.x) * -1;
		btScalar height = (objmodel->BoundingBoxMin.y - objmodel->BoundingBoxMax.y) * -1;
		temp = CreatePhysicsObj(new btCapsuleShape(radius, height), objmodel->MassObject,
			btVector3(objmodel->theTransform.GetPosition().x, objmodel->theTransform.GetPosition().y, objmodel->theTransform.GetPosition().z));
	}
	else {
		btVector3 Shape = btVector3((objmodel->BoundingBoxMax.x - objmodel->BoundingBoxMin.x) / 2, (objmodel->BoundingBoxMax.y - objmodel->BoundingBoxMin.y) / 2, (objmodel->BoundingBoxMax.z - objmodel->BoundingBoxMin.z) / 2);

		temp = CreatePhysicsObj(new btBoxShape(Shape), objmodel->MassObject,
			btVector3(objmodel->theTransform.GetPosition().x, objmodel->theTransform.GetPosition().y, objmodel->theTransform.GetPosition().z));
	}

	temp->GetRigidBody()->getCollisionShape()->setLocalScaling(btVector3(objmodel->theTransform.GetScale().x, objmodel->theTransform.GetScale().y, objmodel->theTransform.GetScale().z));

	return temp;
}

PhysicsObj* SceneWorld::CreatePhysicsObj(btCollisionShape* pShape,
	const float& mass,
	const btVector3& aPosition,
	const btQuaternion& aRotation)
{
	// create a new game object
	PhysicsObj* pPhysicsObject = new PhysicsObj(pShape, mass, aPosition, aRotation);
	float currentm = pShape->getMargin();
	pPhysicsObject->GetRigidBody()->setUserPointer(this);
	pShape->setMargin(0.09f);

	if (DynamicPhysicsWorld)
	{
		DynamicPhysicsWorld->addRigidBody(pPhysicsObject->GetRigidBody());
	}
	else { printf("Attempting to add to a Dynamic world that does not exist\n"); }

	return pPhysicsObject; // return to place in the objects data or in another list
}

void SceneWorld::CalculateWorldPosForInterection(bool& nextScene)
{
	if (GetActivePlayer()->theTransform.GetPosition().x > -12.0f &&
		GetActivePlayer()->theTransform.GetPosition().z > 170.0f &&
		GetActivePlayer()->theTransform.GetPosition().x < 12.0f &&
		GetActivePlayer()->theTransform.GetPosition().z < 175.0f)
	{
		TurnLightOn();
	}
	else if (GetActivePlayer()->theTransform.GetPosition().x > -12.0f &&
		GetActivePlayer()->theTransform.GetPosition().z < -170.0f &&
		GetActivePlayer()->theTransform.GetPosition().x < 12.0f &&
		GetActivePlayer()->theTransform.GetPosition().z > -175.0f)
	{
		nextScene = true;
	}
}


void SceneWorld::CheckForChangeWorld()
{

}

void SceneWorld::SetLocalShaders(Shader* one, Shader* two)
{
	defaultShader = one;
	diffuseShader = two;
}

void SceneWorld::TurnLightOn()
{
#ifdef RASPBERRY
	if (!turnedLightsOn) {
		for (int i = 1; i < meshVector.size(); i++)
		{
			meshVector.at(i)->changeLight = true;
		}
	}
#else
	if (!turnedLightsOn) {
		for (int i = 1; i < meshVector.size(); i++)
		{
			meshVector.at(i)->TheShader = defaultShader;
		}
	}
#endif

}