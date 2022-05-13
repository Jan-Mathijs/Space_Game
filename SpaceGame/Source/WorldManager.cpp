#include "Headers/WorldManager.h"

WorldManager::WorldManager(std::vector<Mesh::DrawObject>& modelVector, Graphics& grap, std::vector<ObjectModel*> MyObjects)
{
	manager = modelVector;
	graphicsPtr = grap;
	myObjects = MyObjects;
}

WorldManager::~WorldManager()
{
	Handler = nullptr;

}

void WorldManager::PrepareScenes()
{
	scenes[0] = new SceneSpace();
	activeScene = scenes[0];

	//scenes[0].nextScene = nextScene;
	float bm[3]{ 0 };
	float bmx[3]{ 0 };


	scenes[0]->sceneShaders = shaders;

	std::string directory("");
	std::string nameObj("");

	Planet* SpaceDome = new Planet(&shaders.at(0), 300, glm::vec3(0), -1, 0);
	//SpaceDome->theSpaceMesh = newMeshManager.LoadMesh("/home/pi/projects/HelloCubes/Resources/ObjFiles/spaceDome.obj");

	//local = PathHandler("cube.obj");
	directory = "Resources/ObjFiles/skybox/";
	nameObj = "Side1.png";
	std::string skyboxTexture = PathHandler(directory, nameObj);//("CubeTexture.jpg");
	directory = "Resources/ObjFiles/skybox/";
	nameObj = "Side2.png";
	std::string skyboxTexture2 = PathHandler(directory, nameObj);
	directory = "Resources/ObjFiles/skybox/";
	nameObj = "Side3.png";
	std::string skyboxTexture3 = PathHandler(directory, nameObj);
	directory = "Resources/ObjFiles/skybox/";
	nameObj = "Side4.png";
	std::string skyboxTexture4 = PathHandler(directory, nameObj);
	directory = "Resources/ObjFiles/skybox/";
	nameObj = "Side5.png";
	std::string skyboxTexture5 = PathHandler(directory, nameObj);
	directory = "Resources/ObjFiles/skybox/";
	nameObj = "Side6.png";
	std::string skyboxTexture6 = PathHandler(directory, nameObj);

	//https://stackoverflow.com/questions/7352099/stdstring-to-char/7352131
	//char* cstr = new char[localTexture.length() + 1];
	//strcpy(cstr, localTexture.c_str());
	//std::vector<char> cstr(localTexture.c_str(), localTexture.c_str() + localTexture.size() + 1);
	char* cstr = &skyboxTexture[0];
	char* cstr2 = &skyboxTexture2[0];
	char* cstr3 = &skyboxTexture3[0];
	char* cstr4 = &skyboxTexture4[0];
	char* cstr5 = &skyboxTexture5[0];
	char* cstr6 = &skyboxTexture6[0];

	//SkyBox* theSkybox = new SkyBox(&shaders.at(0), glm::vec3(0, 0, 10), -1, cstr);
	SkyBox* theSkybox = new SkyBox(cstr, cstr2, cstr3, cstr4, cstr5, cstr6, -1);
	theSkybox->theTransform.SetScale(glm::vec3(15, 15, 15));// = ;
	//theSkybox->WorldPosition = scenes[0].GetActiveCamera()->GetPositon();
	//theSkybox->theMesh->LoadObjAndConvert(bm, bmx, local.c_str());
	scenes[0]->meshVector.push_back(theSkybox);
	theSkybox->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(theSkybox);

	std::string local;
	local = PathHandler("Resources/ObjFiles/", "sun.obj");
	Planet* sun = new Planet(&shaders.at(0), 45.631, glm::vec3(0), 1, 36545.f);
	sun->SetMassPlanet(sun->GetSunMass());
	sun->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);

	SetBoundingBox(sun, bm, bmx);
	sun->theTransform.SetPosition(glm::vec3(0, 0, 0));
	scenes[0]->meshVector.push_back(sun);
	sun->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(sun);

	local = PathHandler("Resources/ObjFiles/", "mercury.obj");
	Planet* mercurius = new Planet(&shaders.at(1), 0.244f, glm::vec3(57.9f * scalerDistance, 0, 0), 3, 0.330f);
	mercurius->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(mercurius, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(mercurius);
	mercurius->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(mercurius);

	local = PathHandler("Resources/ObjFiles/", "venus.obj");
	Planet* venus = new Planet(&shaders.at(1), 0.6052, glm::vec3(108.2f * scalerDistance, 0, 0), 3, 4.87f);
	venus->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(venus, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(venus);
	venus->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(venus);

	local = PathHandler("Resources/ObjFiles/", "earth.obj");
	Planet* earth = new Planet(&shaders.at(1), 0.6371, glm::vec3(149.6f * scalerDistance, 0, 0), 3, 5.972f);
	earth->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(earth, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(earth);
	earth->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(earth);

	local = PathHandler("Resources/ObjFiles/", "astroyedSphere.obj");
	Planet* astoryed = new Planet(&shaders.at(1), 0.6371, glm::vec3(120.0f * scalerDistance, 0, 0), 3, 3.f);
	astoryed->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), true);
	SetBoundingBox(astoryed, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(astoryed);
	astoryed->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(astoryed);

	local = PathHandler("Resources/ObjFiles/", "mars.obj");
	Planet* mars = new Planet(&shaders.at(1), 0.3390, glm::vec3(228 * scalerDistance, 0, 0), 3, 0.642);
	mars->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(mars, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(mars);
	mars->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(mars);

	local = PathHandler("Resources/ObjFiles/", "jupiter.obj");
	Planet* jupiter = new Planet(&shaders.at(1), 6.991, glm::vec3(788.3 * scalerDistance, 0, 0), 3, 1900);
	jupiter->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(jupiter, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(jupiter);
	jupiter->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(jupiter);


	local = PathHandler("Resources/ObjFiles/", "saturnus.obj");
	Planet* saturnus = new Planet(&shaders.at(1), 5.82, glm::vec3(1427 * scalerDistance, 0, 0), 3, 568);
	saturnus->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(saturnus, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(saturnus);
	saturnus->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(saturnus);

	local = PathHandler("Resources/ObjFiles/", "uranus.obj");
	Planet* uranus = new Planet(&shaders.at(1), 2.54, glm::vec3(2871 * scalerDistance, 0, 0), 3, 86.8);
	uranus->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(uranus, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(uranus);
	uranus->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(uranus);

	local = PathHandler("Resources/ObjFiles/", "neptunus.obj");
	Planet* planet1 = new Planet(&shaders.at(1), 2.46, glm::vec3(4498 * scalerDistance, 0, 0), 3, 102.4f);
	planet1->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(planet1, bm, bmx);
	//planet1->SetPosition(glm::vec3(50, 0, 0));
	scenes[0]->meshVector.push_back(planet1);
	planet1->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(planet1);

	SpaceStation* spaceStation = new SpaceStation(&shaders.at(1), 1, glm::vec3(149.6f * scalerDistance, 0, -50), 4, 503.f);
	local = PathHandler("Resources/ObjFiles/SimpleStation/", "spaceStation.obj");
	spaceStation->theSpaceMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(spaceStation, bm, bmx);
	scenes[0]->meshVector.push_back(spaceStation);
	spaceStation->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(spaceStation);

	Player* thePlayer = new Player(&shaders.at(1), 5);
	Camera* theCamera = new Camera(thePlayer->theTransform.GetPosition() + glm::vec3(0, 0, -15), glm::vec3(0, 1, 0));

	theCamera->thePlayer = thePlayer;

	local = PathHandler("Resources/ObjFiles/", "brian_03.obj");
	thePlayer->thePlayerMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(thePlayer, bm, bmx);
	thePlayer->theTransform.SetPosition(glm::vec3(149.6f * scalerDistance, 0, 50));
	//thePlayer->Scales = glm::vec3(1, 1, 1);
	scenes[0]->meshVector.push_back(thePlayer);
	thePlayer->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(thePlayer);

	thePlayer->SetSpaceStationForPlayer(spaceStation);

	scenes[0]->SetCameraScene(theCamera);
	scenes[0]->SetPlayerScene(thePlayer);

	thePlayer->SetInput(theInputWorldManager);
	theSkybox->positionCameraPTR = scenes[0]->GetActiveCamera()->GetPositionPTR();

	//scene two

	SceneWorld* temp = new SceneWorld();

	SkyBox* theSkybox2 = new SkyBox(cstr, cstr2, cstr3, cstr4, cstr5, cstr6, -1);
	theSkybox2->theTransform.SetScale(glm::vec3(15, 15, 15));
	temp->meshVector.push_back(theSkybox2);
	theSkybox2->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(theSkybox2);

	local = PathHandler("Resources/ObjFiles/Modded/", "SpaceStationScene.obj");
	WorldObject* interior = new Ground(&shaders.at(1), 1, 0);
	//interior->theTransform.SetScale(glm::vec3(0.5, 0.5, 0.5));
	interior->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(interior, bm, bmx);
	interior->theTransform.SetPosition(glm::vec3(0, -0.01, 0));
	temp->meshVector.push_back(interior);
	interior->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(interior);

	Ground* plane = new Ground(&shaders.at(0), 3, 0);
	local = PathHandler("Resources/ObjFiles/", "plane2.obj");
	plane->theWorldMesh->LoadObjAndConvertAndPhysicMesh(bm, bmx, local.c_str(), &plane->CollisionMesh);
	plane->theTransform.SetScale(glm::vec3(2, 1, 2));
	SetBoundingBox(plane, bm, bmx);
	plane->Init();
	plane->theTransform.SetPosition(glm::vec3(0, -0.1, 0));
	plane->MyPhysObj = temp->SetPhysicsObject(plane);
	temp->meshVector.push_back(plane);
	plane->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(plane);

	Ground* plane2 = new Ground(&shaders.at(0), 3, 0);
	local = PathHandler("Resources/ObjFiles/", "plane2.obj");
	plane2->theWorldMesh->LoadObjAndConvertAndPhysicMesh(bm, bmx, local.c_str(), &plane2->CollisionMesh);
	//plane->theTransform.SetScale(glm::vec3(10, 10, 10));
	SetBoundingBox(plane2, bm, bmx);
	plane2->Init();
	plane2->theTransform.SetPosition(glm::vec3(0, -0.1, -140));
	plane2->MyPhysObj = temp->SetPhysicsObject(plane2);
	temp->meshVector.push_back(plane2);
	plane2->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(plane2);

	Ground* plane3 = new Ground(&shaders.at(0), 3, 0);
	local = PathHandler("Resources/ObjFiles/", "plane2.obj");
	plane3->theWorldMesh->LoadObjAndConvertAndPhysicMesh(bm, bmx, local.c_str(), &plane3->CollisionMesh);
	//plane->theTransform.SetScale(glm::vec3(10, 10, 10));
	SetBoundingBox(plane3, bm, bmx);
	plane3->Init();
	plane3->theTransform.SetPosition(glm::vec3(0, -0.1, 140));
	plane3->MyPhysObj = temp->SetPhysicsObject(plane3);
	temp->meshVector.push_back(plane3);
	plane3->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(plane3);

	WorldObject* cube1 = new WorldObject(&shaders.at(1), 3, 5);
	local = PathHandler("Resources/ObjFiles/", "crate.obj");
	cube1->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cube1, bm, bmx);
	cube1->theTransform.SetPosition(glm::vec3(0, 2, 0));
	cube1->MyPhysObj = temp->SetPhysicsObject(cube1);
	temp->meshVector.push_back(cube1);
	cube1->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cube1);

	WorldObject* cube2 = new WorldObject(&shaders.at(1), 3, 5);
	local = PathHandler("Resources/ObjFiles/", "crate.obj");
	cube2->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cube2, bm, bmx);
	cube2->theTransform.SetPosition(glm::vec3(0, 2, 0));
	cube2->MyPhysObj = temp->SetPhysicsObject(cube2);
	temp->meshVector.push_back(cube2);
	cube2->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cube2);

	WorldObject* cube3 = new WorldObject(&shaders.at(1), 3, 5);
	local = PathHandler("Resources/ObjFiles/", "crate.obj");
	cube3->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cube3, bm, bmx);
	cube3->theTransform.SetPosition(glm::vec3(0, 2, 0));
	cube3->MyPhysObj = temp->SetPhysicsObject(cube3);
	temp->meshVector.push_back(cube3);
	cube3->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cube3);
	
	WorldObject* cube4 = new WorldObject(&shaders.at(1), 3, 5);
	local = PathHandler("Resources/ObjFiles/", "crate.obj");
	cube4->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cube4, bm, bmx);
	cube4->theTransform.SetPosition(glm::vec3(0, 7, 0));
	cube4->MyPhysObj = temp->SetPhysicsObject(cube4);
	temp->meshVector.push_back(cube4);
	cube4->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cube4);

	WorldObject* cube5 = new WorldObject(&shaders.at(1), 3, 5);
	local = PathHandler("Resources/ObjFiles/", "crate.obj");
	cube5->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cube5, bm, bmx);
	cube5->theTransform.SetPosition(glm::vec3(0, 2, 0));
	cube5->MyPhysObj = temp->SetPhysicsObject(cube5);
	temp->meshVector.push_back(cube5);
	cube5->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cube5);

	Player* thePlayer2 = new Player(&shaders.at(1), 10, 500);
	Camera* theCamera2 = new Camera(thePlayer2->theTransform.GetPosition() + glm::vec3(0, 0, -15), glm::vec3(0, 1, 0));

	theCamera2->thePlayer = thePlayer2;

	local = PathHandler("Resources/ObjFiles/", "HigoCactus.obj");
	thePlayer2->thePlayerMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	thePlayer2->theTransform.SetLocalEulerAngles(glm::vec3(0, 45, 0));
	thePlayer2->theTransform.SetScale(glm::vec3(0.3, 0.3, 0.3));
	SetBoundingBox(thePlayer2, bm, bmx);

	thePlayer2->theTransform.SetPosition(glm::vec3(0, 15, -20));;
	thePlayer2->thePlayerPhysics = temp->SetPhysicsObject(thePlayer2);
	temp->meshVector.push_back(thePlayer2);
	thePlayer2->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(thePlayer2);

	temp->SetCameraScene(theCamera2);
	temp->SetPlayerScene(thePlayer2);

	thePlayer2->SetInput(theInputWorldManager);
	theSkybox2->positionCameraPTR = temp->GetActiveCamera()->GetPositionPTR();
	temp->sceneShaders = shaders;
	local = PathHandler("Resources/Shader/", "SimpleTri.frag");
	std::string local2 = PathHandler("Resources/Shader/", "SimpleTri.vert");
	temp->SetDebugDrawer(local2.c_str(), local.c_str());

	thePlayer2->thePlayerPhysicsDrawPtr = temp->m_pPhysicsDrawer;
	temp->SetLocalShaders(&shaders.at(0), &shaders.at(1));

	temp->SetCameraScene(theCamera2);
	temp->SetPlayerScene(thePlayer2);

	scenes[1] = temp;

	//uncomment to open the bullet test scene
	/*
	SceneWorld* testScene = new SceneWorld();

	WorldObject* cubeTestScene1 = new WorldObject(&shaders.at(0), 3, 500);
	local = PathHandler("Resources/ObjFiles/", "cube.obj");
	cubeTestScene1->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cubeTestScene1, bm, bmx);
	cubeTestScene1->MyPhysObj = testScene->SetPhysicsObject(cubeTestScene1);
	testScene->meshVector.push_back(cubeTestScene1);
	cubeTestScene1->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cubeTestScene1);

	WorldObject* cubeTestScene2 = new WorldObject(&shaders.at(0), 3, 500);
	local = PathHandler("Resources/ObjFiles/", "cube.obj");
	cubeTestScene2->theWorldMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(cubeTestScene2, bm, bmx);
	cubeTestScene2->theTransform.SetPosition(glm::vec3(0, 15, 0));
	cubeTestScene2->MyPhysObj = testScene->SetPhysicsObject(cubeTestScene2);
	testScene->meshVector.push_back(cubeTestScene2);
	cubeTestScene2->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(cubeTestScene2);

	Ground* planeTestScene = new Ground(&shaders.at(0), 3, 0);
	planeTestScene->theTransform.SetPosition(glm::vec3(0, -30, 0));
	local = PathHandler("Resources/ObjFiles/", "plane.obj");
	planeTestScene->theWorldMesh->LoadObjAndConvertAndPhysicMesh(bm, bmx, local.c_str(), &planeTestScene->CollisionMesh);
	SetBoundingBox(planeTestScene, bm, bmx);
	planeTestScene->Init();
	planeTestScene->MyPhysObj = testScene->SetPhysicsObject(planeTestScene);
	testScene->meshVector.push_back(planeTestScene);
	planeTestScene->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(planeTestScene);

	Player* thePlayer3 = new Player(&shaders.at(1), 5, 500);
	Camera* theCamera3 = new Camera(thePlayer3->theTransform.GetPosition() + glm::vec3(0, 0, -15), glm::vec3(0, 1, 0));

	theCamera3->thePlayer = thePlayer3;

	local = PathHandler("Resources/ObjFiles/", "cube.obj");
	thePlayer3->thePlayerMesh->LoadObjAndConvert(bm, bmx, local.c_str(), false);
	SetBoundingBox(thePlayer3, bm, bmx);
	thePlayer3->theTransform.SetPosition(glm::vec3(0, 15, -20));
	//thePlayer->Scales = glm::vec3(1, 1, 1);
	thePlayer3->thePlayerPhysics = testScene->SetPhysicsObject(thePlayer3);
	testScene->meshVector.push_back(thePlayer3);
	thePlayer3->StoreGraphicClass(&graphicsPtr);
	graphicsPtr.Init(thePlayer3);

	testScene->SetCameraScene(theCamera3);
	testScene->SetPlayerScene(thePlayer3);

	thePlayer3->SetInput(theInputWorldManager);// = &theInput;
	testScene->sceneShaders = shaders;
	local = PathHandler("Resources/Shader/", "SimpleTri.frag");
	local2 = PathHandler("Resources/Shader/", "SimpleTri.vert");
	testScene->SetDebugDrawer(local2.c_str(), local.c_str());
	thePlayer3->thePlayerPhysicsDrawPtr = testScene->m_pPhysicsDrawer;

	scenes[2] = testScene;

	activeScene = scenes[2];*/
}

void WorldManager::SetBoundingBox(ObjectModel* objmodel, float min[3], float max[3])
{
	objmodel->BoundingBoxMin.x = objmodel->theTransform.GetScale().x * min[0];
	objmodel->BoundingBoxMin.y = objmodel->theTransform.GetScale().y * min[1];
	objmodel->BoundingBoxMin.z = objmodel->theTransform.GetScale().z * min[2];

	objmodel->BoundingBoxMax.x = objmodel->theTransform.GetScale().x * max[0];
	objmodel->BoundingBoxMax.y = objmodel->theTransform.GetScale().y * max[1];
	objmodel->BoundingBoxMax.z = objmodel->theTransform.GetScale().z * max[2];
}


void WorldManager::MakeScene()
{
	activeScene = scenes[0];
	PrepareScenes();
}

Scene* WorldManager::GetActiveScene()
{
	return activeScene;
}

Shader WorldManager::GetShader()
{
	return theShader;
}

void WorldManager::SetShader(Shader& theShaders)
{
	shaders.push_back(theShaders);

}

void WorldManager::SetCurrentScene(Scene* theScene)
{
	activeScene = scenes[0];
}

std::string WorldManager::GetCurrentWorkingDir() {

	// http://www.codebind.com/cpp-tutorial/c-get-current-directory-linuxwindows/
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);

	bool done = false;
	while (!done)
	{
		std::string replace("\\");
		int posStr = current_working_dir.find(replace);
		if (posStr == -1) {
			done = true;
		}
		else {
			current_working_dir.replace(posStr, replace.length(), "/");
		}
	}

#ifdef RASPBERRY


	std::string temp = "/bin/ARM/Debug";
	current_working_dir.replace(current_working_dir.find("/bin/ARM/Debug"), temp.length(), "");

#endif

	current_working_dir = current_working_dir + "/";
	return current_working_dir;
}

std::string WorldManager::PathHandler(std::string directory, std::string name)
{
	std::string baseRoot = "";


	baseRoot = GetCurrentWorkingDir();

	std::string temp = baseRoot + directory + name;

	return temp;
}

void WorldManager::updateWorldManager(float deltaTime)
{
	waitTime += deltaTime;
	if (nextScene)
	{
		if (waitTime > minWaitTime)
		{
			if (activeScene == scenes[0])
			{
				activeScene = scenes[1];
				scenes[1]->SetFirstCall(false);
				scenes[1]->GetActivePlayer()->SetForce(0.0f);
				scenes[1]->GetActivePlayer()->theTransform.SetPosition(glm::vec3(0.0f, 20.0f, 0.0f));
				nextScene = false;
			}
			else {
				activeScene = scenes[0];
				scenes[0]->GetActivePlayer()->theTransform.SetPosition(scenes[0]->GetActivePlayer()->theTransform.GetPosition() + glm::vec3(0, 0, 5));
				nextScene = false;
			}
			waitTime = 0;
		}


	}
}