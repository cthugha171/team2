#pragma once
#include "Model.h"
#include "Object3d.h"
#include<list>

class CreateObject
{
public:
	CreateObject();
	~CreateObject();

	Object3d* create(Model* model);

private:
	std::list<Object3d*>objList;
};

