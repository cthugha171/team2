#include "CreateObject.h"

CreateObject::~CreateObject()
{
	for (auto objects : objList)
	{
		delete objects;
	}
}

Object3d* CreateObject::create(Model* model)
{
	Object3d* o = Object3d::Create();
	//Model* m = Model::CreateFromOBJ(string);
	o->SetModel(model);

	objList.push_back(o);

	return o;
}
