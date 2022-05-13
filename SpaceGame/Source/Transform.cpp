#include "Headers/Transform.h"
#include <glm/gtx/quaternion.hpp>

//code from Abhishek

Transform::Transform()
{
	Scales = glm::vec3(1.0f);
	Model = glm::mat4(1.0f);
}


Transform::~Transform()
{
}

void Transform::SetPosition(glm::vec3 a_v3Position)
{
	WorldPosition = a_v3Position;
	m_bDirty = true;
}

glm::vec3 Transform::GetPosition()
{
	return WorldPosition;
}

void Transform::SetScale(glm::vec3 a_v3Scale)
{
	Scales = a_v3Scale;
	m_bDirty = true;
}

glm::vec3 Transform::GetScale()
{
	return Scales;
}

void Transform::SetEulerAngles(glm::vec3 a_v3Rotation)
{
	Rotations = a_v3Rotation;

	glm::quat qPitch = glm::angleAxis(Rotations.x, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(Rotations.y, glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(Rotations.z, glm::vec3(0, 0, 1));

	QRotation = qYaw * qPitch * qRoll;

	m_bDirty = true;
}


void Transform::SetRotation(glm::quat a_qRotation)
{
	QRotation = a_qRotation;
	Rotations = glm::eulerAngles(QRotation);

	m_bDirty = true;
}

void Transform::SetLocalRotation(glm::quat a_qRotation)
{
	LocalQRotation = a_qRotation;
	LocalRotations = glm::eulerAngles(LocalQRotation);

	m_bDirty = true;
}

void Transform::Translate(glm::vec3 a_v3Velocity)
{
	SetPosition(GetPosition() + a_v3Velocity);
}

void Transform::Rotate(glm::vec3 a_v3Velocity)
{
	Rotations += a_v3Velocity;

	glm::quat qPitch = glm::angleAxis(Rotations.x, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(Rotations.y, glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(Rotations.z, glm::vec3(0, 0, 1));


	QRotation = qYaw * qPitch * qRoll;

	m_bDirty = true;
}


glm::quat Transform::GetRotation()
{
	return QRotation;
}

glm::vec3 Transform::GetEulerAngles()
{
	return Rotations;
}

glm::vec3 Transform::GetRight()
{
	if (m_bDirty)
		RecalculateMatrix();

	return Right;
}

glm::vec3 Transform::GetLeft()
{
	return -GetRight();
}

glm::vec3 Transform::GetUp()
{
	if (m_bDirty)
		RecalculateMatrix();

	return Up;
}

glm::vec3 Transform::GetDown()
{
	return -GetUp();
}

glm::vec3 Transform::GetForward()
{
	if (m_bDirty)
		RecalculateMatrix();

	return Forward;
}

glm::vec3 Transform::GetBackward()
{
	return -GetForward();
}

glm::mat4 Transform::GetMatrix()
{
	if (m_bDirty)
		RecalculateMatrix();

	return Model;
}

glm::mat4 Transform::GetLocalRotationMatrix()
{
	if (m_bDirtyLocal)
		RecalculateLocalMatrix();

	return mRotationMatrix;
}

glm::mat4 Transform::GetRotationMatrix()
{
	if (m_bDirty)
		RecalculateMatrix();

	return RotationMatrix;
}

void Transform::RecalculateMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), WorldPosition);
	RotationMatrix = glm::toMat4(QRotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), Scales);

	Model = translationMatrix * RotationMatrix * scalingMatrix;

	glm::vec4 x(1, 0, 0, 0);
	glm::vec4 y(0, 1, 0, 0);
	glm::vec4 z(0, 0, 1, 0);
	glm::vec4 o(0, 0, 0, 0);

	x = Model * x;
	y = Model * y;
	z = Model * z;
	o = Model * o;

	Up = glm::vec3(glm::normalize(y - o));
	Forward = glm::vec3(glm::normalize(z - o));
	Right = glm::vec3(glm::normalize(x - o));

	m_bDirty = false;
}

void Transform::RecalculateLocalMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), WorldPosition);
	mRotationMatrix *= glm::toMat4(LocalQRotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), Scales);

	ModelOrientation = translationMatrix * mRotationMatrix * scalingMatrix;

	glm::vec4 x(1, 0, 0, 0);
	glm::vec4 y(0, 1, 0, 0);
	glm::vec4 z(0, 0, 1, 0);
	glm::vec4 o(0, 0, 0, 0);

	x = ModelOrientation * x;
	y = ModelOrientation * y;
	z = ModelOrientation * z;
	o = ModelOrientation * o;

	LocalUp = glm::vec3(glm::normalize(y - o));
	LocalForward = glm::vec3(glm::normalize(z - o));
	LocalRight = glm::vec3(glm::normalize(x - o));

	m_bDirtyLocal = false;
}

void Transform::SetModel(glm::mat4 model)
{
	Model = model;
	m_bDirty = true;
}

void Transform::SetLocalEulerAngles(glm::vec3 local)
{
	LocalRotations = local;

	glm::quat qPitch = glm::angleAxis(LocalRotations.x, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(LocalRotations.y, glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(LocalRotations.z, glm::vec3(0, 0, 1));

	LocalQRotation = qYaw * qPitch * qRoll;

	m_bDirtyLocal = true;
}


glm::vec3 Transform::GetLocalForward()
{
	if (m_bDirtyLocal)
		RecalculateLocalMatrix();
	return LocalForward;
}

glm::vec3 Transform::GetLocalUp()
{
	if (m_bDirtyLocal)
		RecalculateLocalMatrix();
	return LocalUp;
}

glm::mat4 Transform::GetLocalModelMatrix()
{
	if (m_bDirtyLocal)
		RecalculateLocalMatrix();
	return ModelOrientation;
}

void Transform::SetScaleMatrix(glm::mat4 scale)
{
	mScaleMatrix = scale;
}

glm::mat4 Transform::GetScaleMatrix()
{
	return mScaleMatrix;
}

void Transform::SetLocalForward(glm::vec3 forward)
{
	LocalForward = forward;
	m_bDirtyLocal = true;
}

void Transform::SetLocalMatrix(glm::mat4 matrix)
{
	ModelOrientation = matrix;
	//m_bDirtyLocal = true;
}

void Transform::SetLocalRotationMatrix(glm::mat4 matrix)
{
	mRotationMatrix = matrix;
	m_bDirtyLocal = true;
}

