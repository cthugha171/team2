#include "CreateEnemyObject.h"

CreateEnemyObject::~CreateEnemyObject()
{
	for(auto eneObj : objList)
	{
		delete eneObj;
	}
}

Object3d* CreateEnemyObject::create(Model*model)
{
	Object3d* o = Object3d::Create();
	//Model* m = Model::CreateFromOBJ(string);
	o->SetModel(model);

	objList.push_back(o);

	return o;
}
