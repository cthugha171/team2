#include "Building.h"

void Building::Initialize(state state,XMFLOAT2 pos, Object3d* obj,Object3d* obj2)
{
	position = XMFLOAT3({ pos.x,0,100 });
	this->obj = obj;
	this->obj2 = obj2;
	this->obj->SetPosition({position.x+20,position.y,position.z});
	this->obj2->SetPosition({ position.x - 20,position.y,position.z });
	col = new Collision();

	switch (state)
	{
	case high:
		this->obj->SetScale({ 20,200,10 });
		this->obj2->SetScale({ 20,200,10 });
		break;
	case mid:
		this->obj->SetScale({ 10,100,10 });
		this->obj2->SetScale({ 10,100,10 });
		break;
	case low:
		this->obj->SetScale({ 10,50,10 });
		this->obj2->SetScale({ 10,50,10});
	}
}

void Building::Update(Camera* camera)
{
	position.z -= 1;

	obj->SetPosition({ position.x + 100,position.y,position.z });
	obj2->SetPosition({ position.x - 100,position.y,position.z });

	obj->Update(camera->GetmatView(), camera->GetmatProjection());
	obj2->Update(camera->GetmatView(), camera->GetmatProjection());
}

void Building::Draw()
{
	obj->Draw();
	obj2->Draw();
}

bool Building::Collitions(Player* player,Model*mod)
{
	if (col->CheckSphere2Triangle(&player->GetObjectShape(), mod))
	{
		return true;
	}
	return false;
}

XMFLOAT3 Building::GetPosition()
{
	return position;
}
