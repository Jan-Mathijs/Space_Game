#pragma once
#include "tiny_obj_loader.h"
#include <iostream>
#ifdef  RASPBERRY
#include <GLES2/gl2.h>
#else
#include <glad/glad.h>
#endif //  RASPBERRY
#include <algorithm>
#include <glm/vec3.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include "Headers/FastNoise.h"
#include <time.h>

class Mesh
{
public:
	Mesh();
	~Mesh() {};
	std::string GetBaseDir(const std::string& filepath);
	bool LoadObjAndConvert(float bmin[3], float bmax[3], const char* filename, bool prosedural);
	bool LoadObjAndConvertAndPhysicMesh(float bmin[3], float bmax[3], const char* filename, std::vector<btVector3>* mesh);
	void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]);
	bool FileExists(const std::string& abs_filename);
	bool hasSmoothingGroup(const tinyobj::shape_t& shape);
	void computeSmoothingNormals(const tinyobj::attrib_t& attrib, const tinyobj::shape_t& shape, std::map<int, glm::vec3>& smoothVertexNormals);
	void normalizeVector(glm::vec3& v);

	typedef struct {
		GLuint vb_id;  // vertex buffer id
		int numTriangles;
		size_t material_id;
	} DrawObject;
	//virtual void safeData(std::vector<ObjectModel::DrawObject> model, std::map<std::string, GLuint> textures, std::vector<tinyobj::material_t> materials);

	int startValue = 0;

	std::vector<DrawObject> drawObjects;
	std::vector<tinyobj::material_t> materials;
	std::map<std::string, GLuint> textures;


private:

	FastNoise* noice = nullptr;

};

