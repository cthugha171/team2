#pragma once
#include "Model.h"
#include "Object3d.h"
#include<list>
class CreateEnemyObject
{
public:
	~CreateEnemyObject();

	Object3d* create(Model* model);

private:
	std::list<Object3d*>objList;
};

