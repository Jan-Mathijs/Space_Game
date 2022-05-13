#include "Headers/Camera.h"
#include <iostream>

Camera::Camera()
{
	
}

Camera::Camera(glm::vec3 pos, glm::vec3 lookdirection)
{
	positionCamera = pos;
	lookAtCamera = lookdirection;
}


glm::vec3 Camera::GetPositon()
{
	return positionCamera;
}

glm::vec3* Camera::GetPositionPTR()
{
	return &positionCamera;
}

bool Camera::Update(glm::mat4 &View, float deltatime)
{
	if (!thePlayer->GetActiveDockingState()) {
		cameraWantToGoPosition = glm::vec3(thePlayer->theTransform.GetLocalRotationMatrix() * glm::vec4(0, 5.0f, -20.f, 0.0f)) + thePlayer->theTransform.GetPosition();
		positionCamera += (cameraWantToGoPosition - positionCamera) * deltatime * 4.5f;   //add factor delta time
		lookAtCamera = thePlayer->theTransform.GetPosition() + glm::vec3(thePlayer->theTransform.GetLocalRotationMatrix() * glm::vec4(thePlayer->theTransform.GetForward(), 0.0f));
		cameraUp = glm::vec3(thePlayer->theTransform.GetLocalUp());
		View = glm::lookAt(positionCamera, lookAtCamera, cameraUp);
	}
	else {
		positionCamera = thePlayer->GetActiveSpaceStationForPlayer()->theTransform.GetPosition() + glm::vec3(30, 25, 30);
		lookAtCamera = thePlayer->theTransform.GetPosition() + glm::vec3(thePlayer->theTransform.GetLocalRotationMatrix() * glm::vec4(thePlayer->theTransform.GetForward(), 0.0f));
		cameraUp = glm::vec3(thePlayer->theTransform.GetLocalUp());
		View = glm::lookAt(positionCamera, lookAtCamera, cameraUp);
	}
	return true;
}



