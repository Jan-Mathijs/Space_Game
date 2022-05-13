#include "Headers/Player.h"

//constructer for space
Player::Player(Shader* localshader, int typeplayer)
{
	theTransform.SetPosition(glm::vec3(0, 0, -25));
	theTransform.SetScale(glm::vec3(1));
	TheShader = localshader;

	type = typeplayer;

	ThePlayerState = PlayerState::Space;

	BoundingBoxMin = glm::vec3(0);
	BoundingBoxMax = glm::vec3(10);
}

//constructer player for world
Player::Player(Shader* localshader, int typeplayer, float mass)
{
	theTransform.SetPosition(glm::vec3(0, 0, -25));

	theTransform.SetScale(glm::vec3(1));
	TheShader = localshader;

	MassObject = mass;
	type = typeplayer;
	BoundingBoxMin = glm::vec3(0);
	BoundingBoxMax = glm::vec3(10);

	ThePlayerState = PlayerState::World;
}

Player::~Player()
{

}


void Player::AddPosition()
{
	if (thePlayerPhysics == nullptr)
	{
		glm::vec3 temp = glm::vec3(0);
		temp += (theTransform.GetLocalForward() * force);
		theTransform.SetPosition(theTransform.GetPosition() + temp);
	}
	else {

		btVector3 tempForward(theTransform.GetLocalForward().x, theTransform.GetLocalForward().y, theTransform.GetLocalForward().z);
		thePlayerPhysics->GetRigidBody()->applyCentralImpulse(tempForward * force * 50);
		thePlayerPhysics->GetRigidBody()->setAngularVelocity(btVector3(0, -1.0, 0) * LRDIR * 6);
	}

}

void Player::MovementSpace(float deltaTime)
{
	glm::vec3 localrot = glm::vec3(0);

	if (theInputPlayer->inputKeyW)
	{
		force += movementSpeed * deltaTime;
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyS)
	{
		force -= movementSpeed * deltaTime;
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyArrowUp)
	{
		localrot.x -= (movementSpeed * deltaTime);
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyArrowDown)
	{
		localrot.x += (movementSpeed * deltaTime);
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyArrowLeft)
	{
		localrot.y += (movementSpeed * deltaTime);
		InterseptDocking = true;
	}
	if (theInputPlayer->inputKeyArrowRight)
	{
		localrot.y -= (movementSpeed * deltaTime);
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyQ)
	{
		localrot.z -= (movementSpeed * deltaTime);
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyE)
	{
		localrot.z += (movementSpeed * deltaTime);
		InterseptDocking = true;
	}

	if (theInputPlayer->inputKeyZ)
	{
		InterseptDocking = false;
		StartDocking = true;
	}


	theTransform.SetLocalEulerAngles(localrot);

	if (InterseptDocking == true) {
		StartDocking = false;
		firstCall = false;
	}

	if (force >= 1.0f)
	{
		force = 1;
	}
	else
		if (force <= -1.0f)
		{
			force = -1;
		}


}


void Player::MovementWorld(float deltaTime)
{

	if (theInputPlayer->inputKeyW)
	{
		force += movementSpeed * deltaTime;
	}

	if (theInputPlayer->inputKeyS)
	{
		force -= movementSpeed * deltaTime;
	}

	if (theInputPlayer->inputKeyArrowLeft)
	{
		LRDIR = -0.2f;
	}

	if (theInputPlayer->inputKeyArrowRight)
	{
		LRDIR = 0.2f;
	}

	if (theInputPlayer->inputKeyL) {
		if (thePlayerPhysicsDrawPtr != nullptr) {
			thePlayerPhysicsDrawPtr->ToggleDebugFlag(1 + 2);
		}
	}

	if (force >= 1.0f)
	{
		force = 1;
	}
	else
		if (force <= -1.0f)
		{
			force = -1;
		}
}


bool Player::Update(float deltaTime)
{
	theInputPlayer->CheckInput();

	switch (ThePlayerState)
	{
	case PlayerState::Space:
	{
		MovementSpace(deltaTime);

		if (StartDocking == true && InterseptDocking == false)
		{
			Docking(deltaTime);
		}

		AddPosition();
	}
	break;
	case PlayerState::World:
	{
		MovementWorld(deltaTime);
		AddPosition();

		LRDIR = 0;

		if (thePlayerPhysics != nullptr) {
			thePlayerPhysics->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);
			btScalar transform[16]; // physics uses a 16 float matrix syste
			this->thePlayerPhysics->GetTransform(transform);
			btQuaternion orient = this->thePlayerPhysics->GetRigidBody()->getOrientation();
			btVector3 tempvec = btVector3(0, 0, -1);
			btVector3 tempquat = quatRotate(orient, tempvec);
			theTransform.SetLocalRotationMatrix(glm::toMat4(bulletToGlm(orient)));
			glm::vec3 temp;
			temp.x = transform[12];
			temp.y = transform[13];
			temp.z = transform[14]; // don't need the ww.

			theTransform.SetPosition(temp);
			thePlayerPhysics->GetRigidBody()->setDamping(0.2f, 0.15f);
		}
	}
	break;
	default:
		break;
	}

	return true;
}


void Player::Docking(float deltatime)
{
	//check if the spaceStation pointer is zero
	if (spaceStationPlayer == nullptr) return;

	//move towards the space ship
	if (!firstCall) {
		firstCall = true;
		dockPosition = glm::vec3(0);
		lastDockPosition = (theTransform.GetPosition() + glm::vec3((theTransform.GetLocalRotationMatrix() * glm::vec4(dockPosition, 1))));
	}
	dockPosition = spaceStationPlayer->theTransform.GetPosition() + glm::vec3(0, 0, -6);

	lastDockPosition += (dockPosition - lastDockPosition) * deltatime;

	theTransform.SetPosition(lastDockPosition);

	glm::quat playerOrient = glm::quat_cast(theTransform.GetLocalRotationMatrix());
	glm::quat spaceStatingOrient = glm::quat_cast(spaceStationPlayer->theTransform.GetRotationMatrix());
	glm::quat dir(spaceStatingOrient - playerOrient);
	glm::quat target = playerOrient + (dir * 0.5f);// *deltatime;

	theTransform.SetLocalRotationMatrix(glm::mat4_cast(target));	   
}

bool Player::Draw(glm::mat4 Projection, glm::mat4 View)
{
	UpdateShaders(Projection, View);

	if (glGetError() != GL_NO_ERROR)
	{
		printf("Oh bugger  Draw error1\n");
		//  return false;
	}

	for (int i = 0; i < thePlayerMesh->drawObjects.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, thePlayerMesh->drawObjects.at(i).vb_id);
		//TheShader.use();
		int error = 0;
		if ((error = glGetError()) != GL_NO_ERROR)
		{
			printf("Oh bugger  Draw error %i \n", error);
			//return false;
		}
		glEnableVertexAttribArray(this->positionLoc);
		//load the vertex data
		glVertexAttribPointer(this->positionLoc,
			3, // write 3 values
			GL_FLOAT, // they are floats
			GL_FALSE, // not normals
			11 * sizeof(GLfloat),//now many bytes till the next
			0 // where does it start
		); 
		glEnableVertexAttribArray(this->texCoordLoc);
		glVertexAttribPointer(this->texCoordLoc,
			2,
			GL_FLOAT,
			GL_FALSE,
			11 * sizeof(GLfloat),
			(GLfloat*)(9 * sizeof(GLfloat))
		);


		if (normLoc != -1)
		{
			glEnableVertexAttribArray(this->normLoc);
			glVertexAttribPointer(this->normLoc,
				3, // write 3 values
				GL_FLOAT, // they are floats
				GL_TRUE, // not normals
				11 * sizeof(GLfloat),//now many bytes till the next
				(GLfloat*)(3 * sizeof(GLfloat)) // where does it start
			); //
		}

		glBindTexture(GL_TEXTURE_2D, 0);


		if ((error = glGetError()) != GL_NO_ERROR)
		{
			printf("Oh bugger  Draw error %i \n", error);
			//return false;
		}
		if ((thePlayerMesh->drawObjects.at(i).material_id < thePlayerMesh->materials.size())) {
			std::string diffuse_texname = thePlayerMesh->materials[thePlayerMesh->drawObjects.at(i).material_id].diffuse_texname;
			if (thePlayerMesh->textures.find(diffuse_texname) != thePlayerMesh->textures.end()) {
				glBindTexture(GL_TEXTURE_2D, thePlayerMesh->textures[diffuse_texname]);
			}
		}

		//glUniform1i(this->samplerLoc, 0);

		int kaas = 0;
		if ((kaas = glGetError()) != GL_NO_ERROR)
		{
			printf("Oh bugger  Draw error %i \n", kaas);
			//return false
		}

		glDrawArrays(GL_TRIANGLES, 0, thePlayerMesh->drawObjects.at(i).numTriangles * 3);


		if ((error = glGetError()) != GL_NO_ERROR)
		{
			printf("Oh bugger  Draw error %i \n", error);
			//return false;
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Player::UpdateShaders(glm::mat4 Projection, glm::mat4 View)
{
	TheShader->use();

	if (TheShader->ID == 6)
	{
		glm::vec3 lightPosvalue(0);
		TheShader->setVec3("LightPosition", lightPosvalue);

		glm::mat3 rotationMatrixMat3 = glm::transpose(glm::inverse(theTransform.GetLocalModelMatrix()));
		TheShader->setMat3("rotationMatrix", rotationMatrixMat3);

		glm::mat4 MV = theTransform.GetLocalModelMatrix();
		TheShader->setMat4("MV", MV);
	}

	glm::mat4 MVP = Projection * View * theTransform.GetLocalModelMatrix(); // Remember order seems backwards
	TheShader->setMat4("MVP", MVP);

	glm::vec4 Amb(1);
	TheShader->setVec4("Ambient", Amb);

	int error = 0;
	if ((error = glGetError()) != GL_NO_ERROR)
	{
		printf("Oh bugger Draw error %i \n", error);
		//return false;
	}
}

void Player::HandleCollision(ObjectModel* mod)
{
	printf("player reports collision\n");
}

glm::vec3 Player::liniarInterp(glm::vec3 p1, glm::vec3 p2, float t)
{
	glm::vec3 dir = glm::normalize(p2 - p1);

	float dist = length(dir);
	if (dist < 0.01) {
		return p2;
	}

	return p1 * dir * t;
}

ObjectModel* Player::GetActiveSpaceStationForPlayer()
{
	if (spaceStationPlayer != nullptr) {
		return spaceStationPlayer;
	}
}