#include "../Headers/ObjectModel.h"
#include "../Headers/Graphics.h"

using namespace glm;
//******************************************************************************************
// A base container class, containing only information needed to position/rotate and create a model.
// suggest you inherit this
//******************************************************************************************

ObjectModel::ObjectModel()
{
	// really don't want these to do anything
}



ObjectModel::~ObjectModel()
{
	// really don't want these to do anything its up to its derived class to do the housekeeping
}






// set up an already established set of vertices
bool	ObjectModel::LoadModel(GLvoid* a_Vertices)
{
	this->Vertices = a_Vertices;
	return true; // no real reason to return false, but makes sense to give some options
}

/*
// create the modelmatrix by loading the rotations/positions/scale matrices
void		ObjectModel::SetModelMatrix()
{
	//set the matrices we use to I
		mTranslationMatrix	= glm::mat4(1.0f);
	mRotationMatrix		= glm::mat4(1.0f);
	mScaleMatrix		= glm::mat4(1.0f);

	// set scale matrix
		mScaleMatrix = glm::scale(mScaleMatrix, theTransform.GetScale());   // nice easy function
		// set Rotation Matrix
			MakeRotationMatrix();   // this is a bit complex so go do them
			// set translation
				mTranslationMatrix	= glm::translate(mTranslationMatrix, theTransform.GetPosition());   //use the glm translate

				// now make the Model for use in render
					// = mTranslationMatrix * mRotationMatrix * mScaleMatrix;

}

void ObjectModel::MakeTranslationMatrix()
{

	mTranslationMatrix = glm::mat4(1.0f);
	mTranslationMatrix[3][0] = theTransform..x;
	mTranslationMatrix[3][1] = WorldPosition.y;
	mTranslationMatrix[3][2] = WorldPosition.z;
}

// do the rotation matrices
void ObjectModel::MakeRotationMatrix()
{
	// set rotationx
	RotationMatrixX		= glm::mat4(1.0f);
	RotationMatrixX[1][1] = cosf(Rotations.x);
	RotationMatrixX[2][1] = -sinf(Rotations.x);
	RotationMatrixX[1][2] = sinf(Rotations.x);
	RotationMatrixX[2][2] = cosf(Rotations.x);
	//set rotationy
	RotationMatrixY		= glm::mat4(1.0f);
	RotationMatrixY[0][0] = cosf(Rotations.y);
	RotationMatrixY[2][0] = sinf(Rotations.y);
	RotationMatrixY[0][2] = -sinf(Rotations.y);
	RotationMatrixY[2][2] = cosf(Rotations.y);
	//set rotationz
	RotationMatrixZ		= glm::mat4(1.0f);
	RotationMatrixZ[0][0] = cosf(Rotations.z);
	RotationMatrixZ[1][0] = -sinf(Rotations.z);
	RotationMatrixZ[0][1] = sinf(Rotations.z);
	RotationMatrixZ[1][1] = cosf(Rotations.z);

	// now the combined rotation
	mRotationMatrix = RotationMatrixX*RotationMatrixY*RotationMatrixZ;
}
*/
/*
void ObjectModel::MakeRotationMatrixLocal()
{
	// set rotationx
	RotationMatrixX = glm::mat4(1.0f);
	RotationMatrixX[1][1] = cosf(LocalRotations.x);
	RotationMatrixX[2][1] = -sinf(LocalRotations.x);
	RotationMatrixX[1][2] = sinf(LocalRotations.x);
	RotationMatrixX[2][2] = cosf(LocalRotations.x);
	//set rotationy
	RotationMatrixY = glm::mat4(1.0f);
	RotationMatrixY[0][0] = cosf(LocalRotations.y);
	RotationMatrixY[2][0] = sinf(LocalRotations.y);
	RotationMatrixY[0][2] = -sinf(LocalRotations.y);
	RotationMatrixY[2][2] = cosf(LocalRotations.y);
	//set rotationz
	RotationMatrixZ = glm::mat4(1.0f);
	RotationMatrixZ[0][0] = cosf(LocalRotations.z);
	RotationMatrixZ[1][0] = -sinf(LocalRotations.z);
	RotationMatrixZ[0][1] = sinf(LocalRotations.z);
	RotationMatrixZ[1][1] = cosf(LocalRotations.z);

	// now the combined rotation
	mOrientationMatrix *= RotationMatrixX * RotationMatrixY * RotationMatrixZ;
}
*/
/*
// simply create the model matrix, assumes the translations and others have been set
void ObjectModel::MakeModelMatrix()
{
	Model = mTranslationMatrix * mRotationMatrix * mScaleMatrix;
}


// return the position info from worldposition
glm::vec3	ObjectModel::GetPositon()
{
	return WorldPosition;
}



//set the word position
void		ObjectModel::SetPosition(glm::vec3* a_Pos)
{
	WorldPosition.x = 	a_Pos->x;
	WorldPosition.y = 	a_Pos->y;
	WorldPosition.z = 	a_Pos->z;
}
//set the world position
void		ObjectModel::SetPosition(glm::vec3 a_Pos)
{
	WorldPosition = a_Pos;
}

glm::vec3	ObjectModel::GetRotations()
{
	return Rotations;
}
void		ObjectModel::SetRotations(glm::vec3* a_Rots)
{
	Rotations.x = std::fmod(a_Rots->x, 2.0f * PI);
	Rotations.y = std::fmod(a_Rots->y, 2.0f * PI);
	Rotations.z = std::fmod(a_Rots->z, 2.0f * PI);
}

void	ObjectModel::SetRotations(glm::vec3 a_Rots)
{
	Rotations = a_Rots;
}

void		ObjectModel::SetXRotation(float a_x)
{
	Rotations.x = a_x;
}
void		ObjectModel::SetYRotation(float a_y)
{
	Rotations.y = a_y;
}
void		ObjectModel::SetZRotation(float a_z)
{
	Rotations.z = a_z;
}

*/
void ObjectModel::StoreGraphicClass(Graphics* Graphics)
{
	TheGraphics = Graphics;
}