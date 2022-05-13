#pragma once

#include "ObjectModel.h"

class CubeModel : public ObjectModel
{
public:
	CubeModel();
	CubeModel(MyFiles*);

	~CubeModel();

	bool Update(glm::mat4 Projection, glm::mat4 View); // we supply an update system, it can be an all in one system
	bool Draw(); // and a draw 

};
