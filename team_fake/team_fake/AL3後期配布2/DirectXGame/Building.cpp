#include "Building.h"

using namespace DirectX;
using namespace Microsoft::WRL;

void Building::Initialize(state state,XMFLOAT2 pos ,XMFLOAT3 dist , Object3d* obj,Object3d* obj2)
{
	position = XMFLOAT3({ pos.x,0,100 });
	this->dist = dist;
	this->obj = obj;
	this->obj2 = obj2;
	this->obj->SetPosition({position.x+dist.x,position.y,position.z});
	this->obj2->SetPosition({ position.x - dist.x,position.y,position.z });
	col = new Collision();
	rect = new Rectangles();
	rect2 = new Rectangles();

	switch (state)
	{
	case high:
		this->obj->SetScale({ 20,200,10 });
		this->obj2->SetScale({ 20,200,10 });
		rect->size = { 20,200,10 };
		rect2->size = { 20,200,10 };
		break;
	case mid:
		this->obj->SetScale({ 10,100,10 });
		this->obj2->SetScale({ 10,100,10 });
		rect->size = { 10,100,10 };
		rect2->size = { 10,100,10 };
		break;
	case low:
		this->obj->SetScale({ 10,50,10 });
		this->obj2->SetScale({ 10,50,10});
		rect->size = { 10,50,10 };
		rect2->size = { 10,50,10 };
	}
}

void Building::Update(Camera* camera)
{
	position.z -= 1;

	obj->SetPosition({ position.x + dist.x,position.y,position.z });
	obj2->SetPosition({ position.x - dist.x,position.y,position.z });
	rect->center = { position.x + dist.x,position.y,position.z };
	rect2->center = { position.x - dist.x,position.y,position.z };

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
	if (col->SphereToRectangles(&player->GetObjectShape(), rect) || col->SphereToRectangles(&player->GetObjectShape(), rect2))
	{
		return true;
	}

	return false;
}

XMFLOAT3 Building::GetPosition()
{
	return position;
}
