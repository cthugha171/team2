#pragma once
#include "Model.h"
#include "Object3d.h"
#include <list>

class CreateBulletObj
{
public:
	~CreateBulletObj();

	Object3d* create(Model* model);
private:
	std::list<Object3d*>objList;
};

