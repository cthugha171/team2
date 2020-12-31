#include "MoveGround.h"

void MoveGround::Initialize(Object3d* obj,Object3d* obj2, float speed)
{
	first = obj;
	second = obj2;
	first->SetScale({ 50,0,50 });
	second->SetScale({ 50,0,50 });
	firstPos = XMFLOAT3(0, 0, 0);
	secondPos = XMFLOAT3(0, 0, 50);
	first->SetPosition(firstPos);
}

void MoveGround::Update(Camera* camera)
{
	first->SetPosition(firstPos);
	second->SetPosition(secondPos);
	first->Update(camera->GetmatView(), camera->GetmatProjection());
	second->Update(camera->GetmatView(), camera->GetmatProjection());
}

void MoveGround::Draw()
{
	first->Draw();
	second->Draw();
}
