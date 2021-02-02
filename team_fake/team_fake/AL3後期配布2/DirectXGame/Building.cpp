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

	obj->SetPosition({ position.x + dist.x,position.y,position.z });
	obj2->SetPosition({ position.x - dist.x,position.y,position.z });

	obj->Update(camera->GetmatView(), camera->GetmatProjection());
	obj2->Update(camera->GetmatView(), camera->GetmatProjection());
}

void Building::Draw()
{
	obj->Draw();
	obj2->Draw();
}

bool Building::Collitions(Player* player,Model*mod)
{/*
	if (col->CheckSphere2Triangle(&player->GetObjectShape(), mod))
	{
		return true;
	}
	return false;*/
	XMFLOAT3 posA = XMFLOAT3({ position.x + dist.x ,position.y+dist.y,position.z+dist.z});
	XMFLOAT3 posB = XMFLOAT3({ position.x - dist.x ,position.y - dist.y,position.z - dist.z });

	XMFLOAT3 frontA = XMFLOAT3({ posA.x -  obj->GetScale().x / 2 ,posA.y - obj->GetScale().y / 2 ,posA.z - obj->GetScale().y / 2 });
	XMFLOAT3 frontB = XMFLOAT3({ posB.x - obj->GetScale().x / 2 ,posB.y - obj->GetScale().y / 2 ,posB.z - obj->GetScale().y / 2 });

	XMFLOAT3 backA = XMFLOAT3({ posA.x + obj->GetScale().x / 2 ,posA.y + obj->GetScale().y / 2 ,posA.z + obj->GetScale().y / 2 });
	XMFLOAT3 backB = XMFLOAT3({ posB.x + obj->GetScale().x / 2 ,posB.y + obj->GetScale().y / 2 ,posB.z + obj->GetScale().y / 2 });

	if ((player->GetPosition().z >= frontA.z || player->GetPosition().z >= frontB.z) && (player->GetPosition().z <= backA.z || player->GetPosition().z <= backB.z))
	{
		if ((player->GetPosition().x >= frontA.x || player->GetPosition().x >= frontB.x) && (player->GetPosition().x <= backA.x || player->GetPosition().x <= backB.x))
		{
			if ((player->GetPosition().y >= frontA.y || player->GetPosition().y >= frontB.y) && (player->GetPosition().y <= backA.y || player->GetPosition().y <= backB.y))
			{
				return true;
			}

		}
	}
	return false;

}

XMFLOAT3 Building::GetPosition()
{
	return position;
}
