#include "MoveGround.h"

void MoveGround::Initialize(Object3d* obj,Object3d* obj2, float speed)
{
	this->speed = speed;
	first = obj;
	second = obj2;
	first->SetScale({ 50,0,50 });
	second->SetScale({ 50,0,50 });
	firstPos = XMFLOAT3(0, 0, 0);
	secondPos = XMFLOAT3(0, 0, 50);
	first->SetPosition(firstPos);
	second->SetPosition(secondPos);
}

void MoveGround::Update(Camera* camera)
{
	Move();
	first->Update(camera->GetmatView(), camera->GetmatProjection());
	second->Update(camera->GetmatView(), camera->GetmatProjection());
}

void MoveGround::Move()
{
	if (first->GetPosition().z < -50)
	{
		firstPos.z = 50;
	}
	if (second->GetPosition().z < -50)
	{
		secondPos.z = 50;
	}

	firstPos.z -= speed;
	secondPos.z -= speed;

	first->SetPosition(firstPos);
	second->SetPosition(secondPos);
}

void MoveGround::Draw()
{
	first->Draw();
	second->Draw();
}
