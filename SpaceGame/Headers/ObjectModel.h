#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MyFiles.h"
#ifdef RASPBERRY
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif

#include "Shader.h"
#include "tiny_obj_loader.h"

#include "Headers/Transform.h"
#include <bullet/btBulletDynamicsCommon.h>
/* Object model is a base class to represent the most basic form of models
its update and draw classes are pure virtual so any object derived from this must supply those function
It contains simplified matrices for orientation, position and scaling and the ability to create new model matrix before a draw is done
examples of usage can be found in CubeModel
*/

#define PI				3.14159265358979323846264338327950288419716939937510582097494459072381640628620899862803482534211706798f
#define DEG2RAD(x) (x*PI)/180
#define RAD2DEG(x) x*(180/PI)

class Graphics;

inline float Rand(float a_Range) { return (static_cast<float>(rand()) / RAND_MAX)* a_Range; }

//using namespace glm;

class ObjectModel
{
public:
	ObjectModel();
	ObjectModel(MyFiles* FileHandler);
	~ObjectModel();

	Shader* TheShader;

	virtual bool Update(float deltatime) = 0;  // we need to have an Update to move and create the ModelView
	virtual bool Draw(glm::mat4 Projection, glm::mat4 View) = 0;  // and we need to draw from the vertices

	void		SetRotations(glm::vec3*);

	void		StoreGraphicClass(Graphics* Graphics);

	bool		LoadModel(GLvoid* vertices);  // needs expanding 

	void	HandleCollision(ObjectModel*) {}
	glm::vec3	DegreeRotations;

	//source https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=11462
	glm::vec3 bulletToGlm(const btVector3& v) { return glm::vec3(v.getX(), v.getY(), v.getZ()); }
	btVector3 glmToBullet(const glm::vec3& v) { return btVector3(v.x, v.y, v.z); }
	btQuaternion glmToBullet(const glm::quat& q) { return btQuaternion(q.x, q.y, q.z, q.w); }
	glm::quat bulletToGlm(const btQuaternion& q) { return glm::quat(q.getW(), q.getX(), q.getY(), q.getZ()); }

	GLuint texture1;  // a handle to the texture of the mesh/model (can add more if needed or make into an array)

	GLint	positionLoc;  // index handles to important concepts in texture 
	GLint	texCoordLoc;
	GLint   normLoc;
	GLint	samplerLoc;
	glm::vec4	Colour;  // an ambiant colour or tone shade for the model, leave as white for normal

	Graphics* TheGraphics;  // anything that uses a shader will need access to the graphic class set up in the Graphics instance Make sure this is supplied.

	GLvoid* Vertices;  // a pointer to our model array, which should contain vertices and texture coords / expand change as needed 
	GLuint	vbo;

	glm::vec3 BoundingBoxMin;
	glm::vec3 BoundingBoxMax;
	glm::vec3 PrevWorldPosition;

	int type = 0;

	float MassObject = 5;

	Transform theTransform;

	btBvhTriangleMeshShape* mesh;

	bool changeLight = false;
}
;
