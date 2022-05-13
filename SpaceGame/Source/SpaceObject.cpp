#include "Headers/SpaceObject.h"


SpaceObject::SpaceObject()
{

}

SpaceObject::~SpaceObject()
{

}

bool SpaceObject::Update(float deltatime)
{
	//mScaleMatrix = glm::mat4(1.0f);

  //  mScaleMatrix = glm::scale(mScaleMatrix, theTransform.GetScale());

	//CalculateGravatationalForce(this->WorldPosition);

	if (type != -1)
	{
		if (type != 1)
		{
			RotatePlanetSpace(deltatime);
		}
		RotatePlanet(deltatime);
	}

	//  MakeRotationMatrix();
	//  MakeTranslationMatrix();
	 // MakeModelMatrix();
	  //Rotations = glm::vec3(0);
	 // mRotationMatrix = theTransform.GetMatrix();
	  //theTransform.SetRotation(glm::vec3(0));

	return true;
}


bool SpaceObject::Draw(glm::mat4 Projection, glm::mat4 View)
{
	UpdateShaders(Projection, View);

	GLsizei stride = (3 + 3 + 3 + 2) * sizeof(GLfloat); // we have 3x vert, 3x normal,3xcolour,2x texcoord.

	for (int i = theSpaceMesh->startValue; i < theSpaceMesh->drawObjects.size(); i++)
	{
		glDepthFunc(GL_LEQUAL);
		glEnableVertexAttribArray(this->positionLoc);
		glEnableVertexAttribArray(this->texCoordLoc);

		glBindBuffer(GL_ARRAY_BUFFER, theSpaceMesh->drawObjects.at(i).vb_id);
		// TheShader.use();

		 //load the vertex data
		glVertexAttribPointer(this->positionLoc,
			3, // write 3 values
			GL_FLOAT, // they are floats
			GL_FALSE, // not normals
			11 * sizeof(GLfloat),//now many bytes till the next
			0 // where does it start
		); // use 3 values, but add 5 each time to get to the next

	  // Load the texture coordinate
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
				GL_FALSE, // not normals
				11 * sizeof(GLfloat),//now many bytes till the next
				(GLfloat*)(3 * sizeof(GLfloat)) // where does it start
			); //
		}

		//binding the texture with the object
		//bind a empty texture to the obj so it will always be displayed
		glBindTexture(GL_TEXTURE_2D, 0);

		//got these 7 lines from viewer.cc example code tiny obj loader
		//check if there is a texture so yes and is it in range and the correct name give the obj the texture
		if ((theSpaceMesh->drawObjects.at(i).material_id < theSpaceMesh->materials.size())) {
			std::string diffuse_texname = theSpaceMesh->materials[theSpaceMesh->drawObjects.at(i).material_id].diffuse_texname;
			if (theSpaceMesh->textures.find(diffuse_texname) != theSpaceMesh->textures.end()) {
				glBindTexture(GL_TEXTURE_2D, theSpaceMesh->textures[diffuse_texname]);
			}
		}

		glUniform1i(this->samplerLoc, 0);

		glDrawArrays(GL_TRIANGLES, 0, theSpaceMesh->drawObjects.at(i).numTriangles * 3);
		if (glGetError() != GL_NO_ERROR)
		{
			printf("Oh bugger  Draw error\n");
			return false;
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);


	return true;
}

void SpaceObject::RotatePlanet(float deltaTime)
{
	orbit += orbitSpeed;
	DegreeRotations.x = DEG2RAD(orbit.x);
	DegreeRotations.y = DEG2RAD(orbit.y);
	DegreeRotations.z = DEG2RAD(orbit.z);
	//  Rotations += DegreeRotations;
	theTransform.SetEulerAngles(DegreeRotations);
}

void SpaceObject::RotatePlanetSpace(float deltatime)
{
	glm::vec3 directionToSun = glm::normalize(GetSunPosition() - theTransform.GetPosition());
	velocity += directionToSun * (NLOG() * deltatime);
	theTransform.SetPosition(theTransform.GetPosition() + velocity);
}


//const gravitational constant
//fomrulas I used to get the planets rotating 
//mean orbital speed = sqrt((Gravitationalforce * massSun) / distance)
//nlog  GravitationalForce * ((massa1 * massa 2) / (distance ^2)

float SpaceObject::MOS()
{
	//double for precision I only do it once per planet
	double distance = glm::distance(theTransform.GetPosition(), GetSunPosition());
	float  velocitySpeed = sqrt((GravitationalConstant * sunMass) / distance);
	return velocitySpeed;
}

float SpaceObject::NLOG()
{
	float distance = glm::distance(theTransform.GetPosition(), GetSunPosition());
	float force = GravitationalConstant * ((MassObject * sunMass) / (distance * distance));
	return force;
}

void SpaceObject::UpdateShaders(glm::mat4 Projection, glm::mat4 View)
{

	TheShader->use();

	glm::mat4 MVP = Projection * View * theTransform.GetMatrix(); // Remember order seems backwards
	glm::mat4 MV = theTransform.GetMatrix() * View;
	GLuint MatrixID = glGetUniformLocation(TheShader->ID, "MVP"); //LOOK!!!!
	GLuint MVData = glGetUniformLocation(TheShader->ID, "MV");
	GLuint AmbID = glGetUniformLocation(TheShader->ID, "Ambient");
	GLuint LightDir = glGetUniformLocation(TheShader->ID, "LightPosition");
	GLuint roationMatrix = glGetUniformLocation(TheShader->ID, "rotationMatrix");


	float Amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glUniform4fv(AmbID, 1, &Amb[0]);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// glm::mat3 rotationMatrixMat3 = glm::mat3(mRotationMatrix);

	glm::mat3 rotationMatrixMat3 = glm::transpose(glm::inverse(theTransform.GetMatrix()));
	glUniformMatrix3fv(roationMatrix, 1, GL_FALSE, &rotationMatrixMat3[0][0]);

	if (glGetError() != GL_NO_ERROR)
	{
		printf("Oh bugger  Draw error\n");
		//  return false;
	}

	//glm::mat4 MV = Model;
	glUniformMatrix4fv(MVData, 1, GL_FALSE, &MV[0][0]);

	if (glGetError() != GL_NO_ERROR)
	{
		printf("Oh bugger  Draw error\n");
		//return false;
	}


	float lighDirection[3]{ 0,0,0 };
	glUniform3fv(LightDir, 1, &lighDirection[0]);

	if (glGetError() != GL_NO_ERROR)
	{
		printf("Oh bugger  Draw error\n");
		//return false;
	}

}

float SpaceObject::GetMassPlanet()
{
	return MassObject;
}

void SpaceObject::SetMassPlanet(float themass)
{
	MassObject = themass;
}

float SpaceObject::GetSunMass()
{
	return sunMass;
}



