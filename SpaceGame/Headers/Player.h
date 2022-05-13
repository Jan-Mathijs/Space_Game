#pragma once
#include "Mesh.h"
#include "ObjectModel.h"
#include "Input.h"
#include "Shader.h"
#include "Input/BaseInput.h"

#include "PhysicsObj.h"

#ifdef RASPBERRY
#include "Input/LinuxInput.h"
#else
#include "Input/WindowsInput.h"
#endif

class Player : public ObjectModel
{
public:
	Player() {}
	Player(Shader* theShader, int type);
	Player(Shader* theShader, int type, float mass);

	~Player();
	bool Update(float deltatime) override;
	bool Draw(glm::mat4 Projection, glm::mat4 View) override;
	void AddPosition();
	void UpdateShaders(glm::mat4 Projection, glm::mat4 View);

	void MovementSpace(float movementspeed);
	void MovementWorld(float movementSpeed);

	void HandleCollision(ObjectModel*);

	void Docking(float deltaTime);

	PhysicsObj* GetPhysicsObject() { return thePlayerPhysics; }

	Mesh* thePlayerMesh = new Mesh();

	void SetSpaceStationForPlayer(ObjectModel* spaceStation) { spaceStationPlayer = spaceStation; }

	int startvalue = 0;

#ifdef RASPBERRY
	void SetInput(LinuxInput* inp) { theInputPlayer = inp; }
#else
	void SetInput(WindowsInput* inp) { theInputPlayer = inp; }
#endif

	PhysicsObj* thePlayerPhysics = nullptr;
	PhysicsDraw* thePlayerPhysicsDrawPtr = nullptr;

	bool GetActiveDockingState() { return StartDocking; }

	ObjectModel* GetActiveSpaceStationForPlayer();

	void SetForce(float speed) { force = speed; }
private:

	enum class PlayerState {
		Space,
		World,
	};

	PlayerState ThePlayerState = PlayerState::Space;

	glm::vec3 directionPlayer = glm::vec3(0);
	float movespeed = 0.35f;

	float force = 0;

	float pitch = 0;
	float yaw = 0;
	float mouseSensitivity = 0.5f;
	float movementSpeed = 1.0f;

	glm::vec3 liniarInterp(glm::vec3 pi, glm::vec3 p2, float t);

#ifdef RASPBERRY
	LinuxInput* theInputPlayer;
#else.
	WindowsInput* theInputPlayer;
#endif
	float PlayerMass = 0;

	bool InterseptDocking = false;
	bool StartDocking = false;

	ObjectModel* spaceStationPlayer;

	glm::vec3 unitVectorForInterPolation;
	float unitVectorDistance = 0;
	bool interpolating = false;
	glm::vec3 lastDockPosition;
	bool firstCall = false;
	float LRDIR = 0;
	glm::vec3 dockPosition;
};



