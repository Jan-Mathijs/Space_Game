#include "Headers/ObjLoader.h"
#include <stdio.h>
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "Headers/tiny_obj_loader.h"

/*
 * static bool LoadObjAndConvert(float bmin[3], float bmax[3],
							  std::vector<DrawObject>* drawObjects,
							  std::vector<tinyobj::material_t>& materials,
							  std::map<std::string, GLuint>& textures,
							  const char* filename) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;

  timerutil tm;

  tm.start();

  std::string base_dir = GetBaseDir(filename);
  if (base_dir.empty()) {
	base_dir = ".";
  }
 */

