#include "MoveBack.h"


MoveBack::MoveBack(Object3d* obj)
{
	this->obj = obj;
	obj->SetPosition({ 0,0,0 });
	obj->SetScale({ 50,50,50 });
	obj->SetRotation({ 0,0,0 });
}

void MoveBack::Move(Input* input)
{
	if (input->isKeyState(DIK_W))
	{
		rotate.z += 5.0f;
	}
	if (input->isKeyState(DIK_S))
	{
		rotate.z -= 5.0f;
	}
	if (input->isKeyState(DIK_A))
	{
		rotate.x += 5.0f;
	}
	if (input->isKeyState(DIK_D))
	{
		rotate.x -= 5.0f;
	}

	obj->SetRotation(rotate);
}

void MoveBack::Draw()
{
	obj->Draw();
}
