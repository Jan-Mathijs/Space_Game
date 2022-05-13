#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "glm/gtx/quaternion.hpp"

//code from Abhishek

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(glm::vec3 a_v3Position);
	glm::vec3 GetPosition();

	void SetScale(glm::vec3 a_v3Scale);
	glm::vec3 GetScale();

	void SetEulerAngles(glm::vec3 a_v3Rotation);
	void SetLocalEulerAngles(glm::vec3 local);
	void SetRotation(glm::quat a_v3Rotation);
	void SetLocalRotation(glm::quat localRot);
	void Translate(glm::vec3 a_v3Velocity);
	void Rotate(glm::vec3 a_v3Velocity);
	void SetModel(glm::mat4 model);
	void SetScaleMatrix(glm::mat4 scale);
	void SetLocalForward(glm::vec3 forward);
	glm::mat4 GetScaleMatrix();
	glm::vec3 GetEulerAngles();
	glm::quat GetRotation();

	glm::vec3 GetRight();
	glm::vec3 GetLeft();
	glm::vec3 GetUp();
	glm::vec3 GetDown();
	glm::vec3 GetForward();
	glm::vec3 GetBackward();
	glm::mat4 GetRotationMatrix();
	glm::vec3 GetLocalForward();
	glm::vec3 GetLocalUp();
	glm::mat4 GetMatrix();
	glm::mat4 GetLocalModelMatrix();

	glm::mat4 GetLocalRotationMatrix();

	void SetLocalMatrix(glm::mat4 matrix);
	void SetLocalRotationMatrix(glm::mat4 matrix);


private:
	void RecalculateMatrix();
	void RecalculateLocalMatrix();

	glm::vec3 WorldPosition{ 1,1,1 };
	glm::vec3 Scales{ 1,1,1 };
	glm::vec3 Rotations{ 1,1,1 };
	glm::vec3 LocalRotations{ 1,1,1 };
	glm::vec3 Forward{ 0,0,1 };
	glm::vec3 Up{ 0,1,0 };
	glm::vec3 Right{ 1,0,0 };
	glm::quat QRotation = glm::quat(1, 0, 0, 0);
	glm::quat LocalQRotation = glm::quat(1, 0, 0, 0);

	glm::mat4 Model = glm::mat4(1);
	glm::mat4 ModelOrientation = glm::mat4(1);
	glm::mat4 mRotationMatrix{ 1 };
	glm::mat4 RotationMatrix{ 1 };

	glm::vec3 LocalForward{ 0,0,1 };
	glm::vec3 LocalUp{ 0,1,0 };
	glm::vec3 LocalRight{ 1,0,0 };
	glm::mat4 mScaleMatrix{ 1 };

	bool m_bDirty;
	bool m_bDirtyLocal;
};



