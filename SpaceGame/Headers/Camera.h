#pragma once
#ifdef RASPBERRY
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif
#include <math.h>
#include <glm/detail/type_mat2x2.hpp>
#include "Input.h"
#include "ObjectModel.h"
#include "Player.h"

class Camera 
{
private:
	glm::mat4 cameraMatrix;
	char keyInput[512];

	glm::vec3 positionCamera = glm::vec3(0, 0, -10.0f);
	glm::vec3 cameraWantToGoPosition = glm::vec3(0);
	glm::vec3 WorldUp;
	glm::vec3 lookAtCamera = glm::vec3(0, 0, 1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	float cameraSpeed = 0.2f;
	float mouseSensitivity;

	//brians code : 
	glm::vec3 Rotations; //stored as radians
	
public:
	//default
	Camera();

	Camera(glm::vec3 pos, glm::vec3 lookat);
	//Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	~Camera();

	glm::mat4 CameraUpdate();
	
	void SetPosition(glm::vec3 Position);
	
	void AddPosition(glm::vec3 addedPosition);
	
	glm::vec3 GetPositon();

	glm::vec3* GetPositionPTR();

	bool Update(glm::mat4 &View, float deltatime);

	Player* thePlayer = nullptr;

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(positionCamera, positionCamera + cameraDirection, cameraUp);
	}
	
};


