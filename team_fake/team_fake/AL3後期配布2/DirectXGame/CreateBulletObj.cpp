#include "CreateBulletObj.h"

CreateBulletObj::~CreateBulletObj()
{
	for (auto bullets : objList)
	{
		delete bullets;
	}
}

Object3d* CreateBulletObj::create(Model* model)
{
	Object3d* o = Object3d::Create();
	//Model* m = Model::CreateFromOBJ(string);
	o->SetModel(model);

	objList.push_back(o);

	return o;
}
